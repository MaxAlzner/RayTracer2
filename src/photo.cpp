
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Image;
		using namespace Mesh;
		using namespace Components;

		RAY_API void Photo::build()
		{
			this->hits = new HitBuffer(this->width, this->height, this->reflectDepth);
		}
		RAY_API void Photo::dispose()
		{
			if (this->hits != 0)
			{
				delete this->hits;
				this->hits = 0;
			}
		}

		RAY_API bool Photo::isEmpty() const
		{
			return this->width < 1 && this->height < 1;
		}

		RAY_API Surface* Photo::flatten() const
		{
			Surface* surface = new Surface;
			surface->build();
			surface->reformat(PIXELFORMAT::PIXELFORMAT_RGBA);
			surface->resize(this->width, this->height);

			for (int i = 0; i < this->height; i++)
			{
				for (int k = 0; k < this->width; k++)
				{
					rayhit hit = this->hits->get(k, i);

					Color color;
					//color = Color((hit.normal.x + 1.0f) / 2.0f, (hit.normal.y + 1.0f) / 2.0f, (hit.normal.z + 1.0f) / 2.0f, 1.0f);
					//color = Color(hit.texcoord.x, hit.texcoord.y, 0.0f, 1.0f);

					surface->put(k, this->height - (i + 1), hit.shape != 0 ? EncodeColor(color, surface->format()) : (EncodedPixel)0xFF000000);
				}
			}

			return surface;
		}

		RAY_API void Photo::emit(TraceStack* stack)
		{
			if (stack != 0 && stack->camera != 0)
			{
				this->hits->clear();
				for (ListIterator<Entity*>* i = stack->stack.iterator(); i->inside(); i->next())
				{
					Entity* entity = i->current();
					if (entity != 0)
					{
						entity->transform->recalculate();
					}
				}

				stack->camera->adjust();
				for (int i = 0; i < this->height; i++)
				{
					for (int k = 0; k < this->width; k++)
					{
						rayhit hit = this->trace(k, i, stack);

						if (hit.shape != 0)
						{
							this->hits->get(k, i) = hit;
						}
					}
				}
			}
		}

		RAY_API rayhit Photo::trace(int x, int y, TraceStack* stack)
		{
			if (stack != 0)
			{
				float cutoff = FLT_MAX;
				rayhit hit;
				for (ListIterator<Entity*>* i = stack->stack.iterator(); i->inside(); i->next())
				{
					Entity* entity = i->current();
					if (entity != 0 && entity->meshfilter != 0 && entity->meshfilter->shape != 0)
					{
						ray ray = stack->camera->getRay(float(x) / float(this->width), float(y) / float(this->height));
						rayhit newHit;
						transformation<float> transform(entity->transform->position, entity->transform->scale, entity->transform->space);
						
						if (entity->meshfilter->shape->hitByRay(ray, transform, &newHit) && newHit.distance < cutoff)
						{
							cutoff = newHit.distance;
							hit = newHit;
						}
					}
				}

				return hit;
			}

			return rayhit();
		}

	}
}