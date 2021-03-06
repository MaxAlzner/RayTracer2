
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

			inline RAY_API Lumination CookTorranceMaterial::shade(const Lighting& lighting, const Fragment& fragment) const
			{
				vec3 h = normalize(fragment.normal + fragment.view);

				float n_dot_l = dot(fragment.normal, lighting.light);
				float n_dot_h = dot(fragment.normal, h);
				float n_dot_v = dot(fragment.normal, fragment.view);
				float h_dot_v = dot(h, fragment.view);
				float h_dot_l = dot(h, fragment.view);

				float diffuse = clamp(n_dot_l, 0.0f, 1.0f);

				float g1 = (2.0f * n_dot_h * n_dot_v) / h_dot_v;
				float g2 = (2.0f * n_dot_h * n_dot_l) / h_dot_v;
				float g = 1.0f;
				if (g1 < g) g = g1;
				if (g2 < g) g = g2;
				float m = this->roughness * this->roughness;
				float r = (1.0f / (m * pow(n_dot_h, 4.0f))) * exp((pow(n_dot_h, 2.0f) - 1.0f) / (m * pow(n_dot_h, 2.0f)));
				float f = (this->refractionIndex + pow(1.0f - h_dot_v, 5.0f)) * (1.0f - this->refractionIndex);
				float brdf = clamp((abs(f * r * g) / n_dot_v), 0.0f, 1.0f);

				return Lumination(fragment.color * Color(diffuse * lighting.attenuation), fragment.specular * Color(brdf * diffuse * lighting.attenuation));
			}

			inline Lumination CookTorranceMaterial::reflection(const Lumination& albedo, const Fragment& fragment) const
			{
				return Lumination(0.0f, 0.0f);
			}

		}
	}
}