
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		inline RAY_API void Fragment::resample()
		{
			if (this->material != 0)
			{
				this->color = this->material->surfaceColor(this->texcoord);
				this->specular = this->material->surfaceSpecular(this->texcoord);
				this->transparency = this->material->surfaceTransparency(this->texcoord);
				this->reflectivity = this->material->surfaceReflectivity(this->texcoord);
				this->emissive = this->material->surfaceEmissive(this->texcoord);
			}
		}
		inline RAY_API void Fragment::adjust(const RayHit& hit)
		{
			this->position = hit.intersection;
			this->texcoord = hit.texcoord;
			this->view = -hit.ray.direction;

			if (this->material != 0)
			{
				vec3 surfaceNormal = this->material->surfaceNormal(this->texcoord);
				mat3 space(hit.tangent, hit.binormal, hit.normal);

				this->normal = normalize(space * surfaceNormal);
				this->tangent = cross(-hit.binormal, this->normal);
				this->binormal = cross(this->tangent, this->normal);
			}
		}

		inline RAY_API ray Fragment::reflect(const ray& r)
		{
			return ray(this->position, glm::reflect(-r.direction, this->normal));
		}

	}
}