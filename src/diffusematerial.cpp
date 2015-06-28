
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

			inline RAY_API Lumination DiffuseMaterial::shade(const Lighting& lighting, const Fragment& fragment) const
			{
				float n_dot_l = Math::dot(lighting.light, fragment.normal);

				float diffuse = Math::clamp(n_dot_l, 0.0f, 1.0f);
				
				return Lumination(fragment.color * Color(diffuse * lighting.attenuation), Color(0.0f));
			}

			inline Lumination DiffuseMaterial::reflection(const Lumination& albedo, const Fragment& fragment) const
			{
				return Lumination(0.0f, 0.0f);
			}

		}
	}
}