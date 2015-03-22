#ifndef RAY_COMPONENT_H
#define RAY_COMPONENT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Component
		{
		public:

			inline Component() : object(0) {}
			inline Component(String type) : object(0), type(type) {}
			inline ~Component() {}

			String type;
			Tracer::Entity* object;

		};

	}
}

#endif