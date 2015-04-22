
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Threading;
		using namespace Object::Image;
		using namespace Object::Mesh;

		using namespace DataObjects;
		using namespace Components;
		using namespace Components::Lights;

		RAY_API void Photo::build()
		{
			this->reflectDepth = Math::max(this->reflectDepth, 0);
			this->multiSampleDepth = Math::max(this->multiSampleDepth, 0);
			//this->_geometrypass = Map<RayHit>(this->_width, this->_height, this->reflectDepth + 1);
			//this->_fragmentpass = Map<Fragment>(this->_width, this->_height, this->reflectDepth + 1);
			this->_geometrypass = Map<TracePath>(this->_width, this->_height);
			this->_lightpass = Map<Lumination>(this->_width, this->_height);
		}
		RAY_API void Photo::dispose()
		{
			this->_geometrypass.clear();
			this->_lightpass.clear();
		}

		RAY_API bool Photo::isEmpty() const
		{
			return this->_width < 1 && this->_height < 1;
		}

		RAY_API Surface* Photo::flatten()
		{
			Surface* surface = new Surface;
			surface->build();
			surface->reformat(PIXELFORMAT::PIXELFORMAT_RGBA);
			surface->resize(this->_width, this->_height);

			for (int i = 0; i < this->_height; i++)
			{
				for (int k = 0; k < this->_width; k++)
				{
					Lumination luminance = this->_lightpass.get(k, i);
					//Fragment fragment = this->_fragmentpass.get(k, i);

					Color color = luminance.diffuse + luminance.specular;

					//color = Color(fragment.texcoord.x, fragment.texcoord.y, 0.0f, 1.0f);
					//color = luminance.specular;

					color.a = 1.0f;
					surface->put(k, this->_height - (i + 1), EncodeColor(color, surface->format()));
				}
			}

			return surface;
		}

		RAY_API void Photo::render(TraceStack* stack)
		{
			if (stack != 0 && stack->camera != 0)
			{
				this->_geometrypass.zero();
				this->_lightpass.zero();
				for (Iterator<Entity*> i = stack->stack.iterator(); i.inside(); i.next())
				{
					Entity* entity = i.current();
					if (entity != 0)
					{
						entity->transform->recalculate();
					}
				}

				stack->camera->adjust();

				const int sections = 8;
				const int section = this->_height / sections;
				List<PhotoEmitter*> emitters;
				List<Thread*> threads;
				for (int i = 0; i < sections; i++)
				{
					PhotoEmitter* emitter = new PhotoEmitter(this, stack, ibox(ivec2(0, section * i), ivec2(this->_width, section * (i + 1))));
					emitters.add(emitter);
					Thread* thread = new Thread;
					thread->callstack += Photo::_renderCallback;
					thread->callstack.setData(emitter);
					threads.add(thread);
				}

				for (Iterator<Thread*> i = threads.iterator(); i.inside(); i.next())
				{
					Thread* thread = i.current();
					if (thread != 0)
					{
						thread->start();
					}
				}

				while (true)
				{
					bool finished = true;
					for (Iterator<Thread*> i = threads.iterator(); i.inside(); i.next())
					{
						Thread* thread = i.current();
						if (thread != 0)
						{
							finished = finished && thread->finished();
						}
					}

					if (finished)
					{
						break;
					}
				}

				for (Iterator<PhotoEmitter*> i = emitters.iterator(); i.inside(); i.next())
				{
					PhotoEmitter* emitter = i.current();
					if (emitter != 0)
					{
						delete emitter;
					}
				}

				for (Iterator<Thread*> i = threads.iterator(); i.inside(); i.next())
				{
					Thread* thread = i.current();
					if (thread != 0)
					{
						delete thread;
					}
				}

				emitters.clear();
				threads.clear();
			}
		}

		RAY_API unsigned int _stdcall Photo::_renderCallback(void* data)
		{
			PhotoEmitter* emitter = (PhotoEmitter*)data;
			if (emitter != 0)
			{
				emitter->emit();
				return 0;
			}

			return -1;
		}

	}
}