#ifndef RAY_AREALIGHT_H
#define RAY_AREALIGHT_H

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{

			class RAY_API AreaLight : public Light
			{
			public:

				inline AreaLight() :
					Light() {}
				inline AreaLight(const glm::vec2& area, const float intensity) :
					Light(intensity),
					area(area) {}
				inline virtual ~AreaLight() {}

				inline DataObjects::Lumination luminance(const DataObjects::Fragment& fragment);

				inline float occlusion(const DataObjects::Fragment& fragment);

				glm::vec2 area;

			};

		}
	}
}

#endif