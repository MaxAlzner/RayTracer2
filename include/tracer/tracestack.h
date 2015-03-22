#ifndef RAY_TRACESTACK_H
#define RAY_TRACESTACK_H

namespace RAY_NAMESPACE
{
	namespace Tracer
	{

		class RAY_API TraceStack : public IObject
		{
		public:

			inline TraceStack() {}
			inline ~TraceStack() {}

			virtual void build();
			virtual void dispose();

			virtual bool isEmpty() const;

			void add(Entity* entity);

			Collection::List<Entity*> stack;
			Components::Camera* camera;

		};

	}
}

#endif