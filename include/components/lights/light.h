#ifndef RAY_LIGHT_H
#define RAY_LIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{

			class RAY_API Light : public Component
			{
			public:

				inline Light() :
					Component("Light"),
					intensity(1.0f) {}
				inline Light(const float intensity) :
					Component("Light"),
					intensity(intensity) {}
				inline ~Light() {}

				virtual inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment) = 0;

				virtual inline float occlusion(const DataObjects::Fragment& fragment) = 0;

				float intensity;

			protected:

			};

		}
	}
}

#endif