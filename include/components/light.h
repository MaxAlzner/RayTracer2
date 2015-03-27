#ifndef RAY_LIGHT_H
#define RAY_LIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Light : public Component
		{
		public:

			inline Light() :
				Component("Light"),
				intensity(1.0f) {}
			inline ~Light() {}

			virtual inline Tracer::Lumination luminate(const Tracer::Entity* entity) = 0;

			virtual inline bool hitByLight(const Tracer::Entity* entity) = 0;

			float intensity;

		protected:

		};

	}
}

#endif