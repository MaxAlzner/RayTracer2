
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{
			using namespace DataObjects;
			using namespace Tracer;

			inline RAY_API Lumination PhongMaterial::shade(const Lighting& lighting, const Fragment& fragment) const
			{
				vec3 r = glm::reflect(-lighting.light, fragment.normal);

				float n_dot_l = dot(lighting.light, fragment.normal);
				float r_dot_v = dot(r, fragment.view);

				float diffuse = clamp(n_dot_l, 0.0f, 1.0f);

				float phong = clamp(pow(r_dot_v, this->exponent), 0.0f, 1.0f);

				return Lumination(fragment.color * Color(diffuse * lighting.attenuation), fragment.specular * Color(phong * diffuse * lighting.attenuation));
			}

			inline Lumination PhongMaterial::reflection(const Lumination& albedo, const Fragment& fragment) const
			{
				return Lumination(0.0f, 0.0f);
			}

		}
	}
}