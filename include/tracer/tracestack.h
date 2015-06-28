#ifndef RAY_TRACESTACK_H
#define RAY_TRACESTACK_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API TraceStack : public IObject
		{
		public:

			inline TraceStack() :
				camera(0) {}
			inline ~TraceStack() {}

			void build();
			void dispose();

			bool isEmpty() const;

			DataObjects::Fragment trace(const ray& ray, DataObjects::RayHit* hit);
			DataObjects::Lumination albedo(const TracePath& path);

			void add(Entity* entity);

			Collection::List<Entity*> stack;
			Collection::List<Components::Lights::Light*> lights;
			Components::Cameras::Camera* camera;

		};

	}
}

#endif