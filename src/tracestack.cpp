
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace Collection;
		using namespace Object::Mesh;
		using namespace DataObjects;
		using namespace Components;
		using namespace Components::Materials;
		using namespace Components::Cameras;
		using namespace Components::Lights;

		RAY_API void TraceStack::build()
		{

		}
		RAY_API void TraceStack::dispose()
		{
			for (Iterator<Entity*> i = this->stack.iteratorAtEnd(); i.inside(); i.previous())
			{
				Entity* entity = i.current();
				if (entity != 0)
				{
					delete entity;
				}
			}

			this->stack.clear();
		}

		RAY_API bool TraceStack::isEmpty() const
		{
			return this->stack.count() < 1;
		}

		RAY_API Entity* TraceStack::trace(const ray& ray, RayHit* hit)
		{
			float cutoff = FLT_MAX;
			Entity* nearest = 0;
			for (Iterator<Entity*> i = this->stack.iterator(); i.inside(); i.next())
			{
				Entity* entity = i.current();
				if (entity != 0 && entity->meshfilter != 0 && entity->meshfilter->shape != 0)
				{
					RayHit test;
					transformation<float> transform(entity->transform->position, entity->transform->scale, entity->transform->space);

					if (entity->meshfilter->shape->hitByRay(ray, transform, &test) && test.distance < cutoff)
					{
						cutoff = test.distance;
						nearest = entity;
						if (hit != 0)
						{
							*hit = test;
						}
					}
				}
			}

			return nearest;
		}
		RAY_API Lumination TraceStack::albedo(const Fragment& fragment)
		{
			Lumination albedo;
			for (Iterator<Light*> i = this->lights.iterator(); i.inside(); i.next())
			{
				Light* light = i.current();
				albedo += light->luminance(fragment);
			}

			return albedo;
		}

		RAY_API void TraceStack::add(Entity* entity)
		{
			if (entity != 0)
			{
				entity->stack = this;
				this->stack.add(entity);

				Camera* camera = (Camera*)entity->findComponent("Camera");
				if (camera != 0)
				{
					this->camera = camera;
				}

				Light* light = (Light*)entity->findComponent("Light");
				if (light != 0)
				{
					this->lights.add(light);
				}
			}
		}

	}
}