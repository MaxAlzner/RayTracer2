#ifndef RAY_SPOTLIGHT_H
#define RAY_SPOTLIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{

			class RAY_API SpotLight : public Light
			{
			public:

				inline SpotLight() :
					Light(),
					angle(60.0f) {}
				inline SpotLight(const float angle, const float intensity) :
					Light(intensity),
					angle(angle) {}
				inline ~SpotLight() {}

				inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment);

				inline float occlusion(const DataObjects::Fragment& fragment);

				float angle;

			};

		}
	}
}

#endif