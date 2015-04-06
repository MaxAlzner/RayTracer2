#ifndef RAY_LIGHTING_H
#define RAY_LIGHTING_H

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		class RAY_API Lighting
		{
		public:

			inline Lighting() :
				light(0.0f, 0.0f, 1.0f),
				attenuation(0.0f) {}
			inline Lighting(const vec3& light, const float attenuation) :
				light(light),
				attenuation(attenuation) {}
			inline ~Lighting() {}

			vec3 light;
			float attenuation;

		};

	}
}

#endif