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
				inline ~PointLight() {}

				inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment);

				inline bool occluded(const DataObjects::Fragment& fragment);

			};

		}
	}
}

#endif