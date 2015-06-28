#ifndef RAY_POINTLIGHT_H
#define RAY_POINTLIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{

			class RAY_API PointLight : public Light
			{
			public:

				inline PointLight() :
					Light() {}
				inline PointLight(const float intensity) :
					Light(intensity) {}
				inline virtual ~PointLight() {}

				inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment);

				inline float occlusion(const DataObjects::Fragment& fragment);

			};

		}
	}
}

#endif