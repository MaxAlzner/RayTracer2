#ifndef RAY_TRACESTACK_H
#define RAY_TRACESTACK_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API TraceStack : public Object
		{
		public:

			inline TraceStack() :
				camera(0) {}
			inline ~TraceStack() {}

			void build();
			void dispose();

			bool empty() const;

			DataObjects::Fragment trace(const ray& ray, DataObjects::RayHit* hit);
			DataObjects::Lumination albedo(const TracePath& path);

			void add(Entity* entity);

			List<Entity*> stack;
			List<Components::Lights::Light*> lights;
			Components::Cameras::Camera* camera;

		};

	}
}

#endif