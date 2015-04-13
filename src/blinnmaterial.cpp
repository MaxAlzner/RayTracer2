
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

			inline RAY_API Lumination BlinnMaterial::shade(const Lighting& lighting, const Fragment& fragment) const
			{
				vec3 h = Math::normalize(fragment.normal + fragment.view);

				float n_dot_l = Math::dot(lighting.light, fragment.normal);
				float h_dot_v = Math::dot(h, fragment.view);

				float diffuse = Math::clamp(n_dot_l, 0.0f, 1.0f);

				float blinn = Math::clamp(pow(h_dot_v, this->exponent), 0.0f, 1.0f);

				return Lumination(fragment.color * Color(diffuse * lighting.attenuation), fragment.specular * Color(blinn * diffuse * lighting.attenuation));
			}

		}
	}
}