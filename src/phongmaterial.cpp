
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
				vec3 r = Math::reflect(-lighting.light, fragment.normal);

				float n_dot_l = Math::dot(lighting.light, fragment.normal);
				float r_dot_v = Math::dot(r, fragment.view);

				float diffuse = Math::clamp(n_dot_l, 0.0f, 1.0f);

				float phong = Math::clamp(pow(r_dot_v, this->exponent), 0.0f, 1.0f);

				return Lumination(fragment.color * Color(diffuse * lighting.attenuation), Color(phong * lighting.attenuation * fragment.specular));
			}

		}
	}
}