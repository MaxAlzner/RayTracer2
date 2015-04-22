#ifndef RAY_DIRECTIONALLIGHT_H
#define RAY_DIRECTIONALLIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{

			class RAY_API DirectionalLight : public Light
			{
			public:

				inline DirectionalLight() :
					Light() {}
				inline DirectionalLight(const float intensity) :
					Light(intensity) {}
				inline ~DirectionalLight() {}

				inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment);

				inline float occlusion(const DataObjects::Fragment& fragment);

			};

		}
	}
}

#endif