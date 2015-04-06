
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
			this->_geometrypass = Map<RayHit>(this->_width, this->_height, this->reflectDepth);
			this->_fragmentpass = Map<Fragment>(this->_width, this->_height, this->reflectDepth);
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

					Color color = luminance.diffuse + luminance.specular;
					color.a = 1.0f;

					//surface->put(k, this->_height - (i + 1), hit.shape != 0 ? EncodeColor(color, surface->format()) : (EncodedPixel)0xFF000000);
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

				//PhotoEmitter* emitter0 = new PhotoEmitter(this, stack, ibox(ivec2(0, section * 0), ivec2(this->_width, section * 1)));
				//PhotoEmitter* emitter1 = new PhotoEmitter(this, stack, ibox(ivec2(hw, 0), ivec2(this->_width, hh)));
				//PhotoEmitter* emitter2 = new PhotoEmitter(this, stack, ibox(ivec2(0, hh), ivec2(hw, this->_height)));
				//PhotoEmitter* emitter3 = new PhotoEmitter(this, stack, ibox(ivec2(hw, hh), ivec2(this->_width, this->_height)));

				//Thread* thread0 = new Thread;
				//thread0->callstack += Photo::_renderCallback;
				//thread0->callstack.setData(emitter0);
				//Thread* thread1 = new Thread;
				//thread1->callstack += Photo::_renderCallback;
				//thread1->callstack.setData(emitter1);
				//Thread* thread2 = new Thread;
				//thread2->callstack += Photo::_renderCallback;
				//thread2->callstack.setData(emitter2);
				//Thread* thread3 = new Thread;
				//thread3->callstack += Photo::_renderCallback;
				//thread3->callstack.setData(emitter3);

				//thread0->start();
				//thread1->start();
				//thread2->start();
				//thread3->start();

				//while (true)
				//{
				//	if (thread0->finished() && thread1->finished() && thread2->finished() && thread3->finished())
				//	{
				//		break;
				//	}
				//}
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