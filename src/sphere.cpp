
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace DataObjects;

		RAY_API bool Sphere::hitByRay(const ray& ray, const transformation<float>& trans, RayHit* hit)
		{
			float radius = glm::length(trans.scale);
			vec3 p = (ray.origin - trans.translation);
			float a = dot(ray.direction, ray.direction);
			float b = dot((p * 2.0f), ray.direction);
			float c = dot(p, p) - (radius * radius);
			float d = (b * b) - (4.0f * a * c);

			if (d >= 0.0f)
			{
				float e = sqrt(d);

				float t0 = (-b - e) / (2.0f * a);
				float t1 = (-b + e) / (2.0f * a);

				if (t0 >= 0.0f && t1 >= 0.0f)
				{
					float t = t0 < t1 ? t0 : t1;

					if (t <= ray.length)
					{
						vec3 intersection = ray.origin + (ray.direction * t);
						vec3 normal = glm::normalize(intersection - trans.translation);
						vec3 tangent = cross(normal, vec3(0.0f, 1.0f, 0.0f));
						vec3 binormal = cross(normal, tangent);

						if (dot(normal, ray.direction) < 0.0f)
						{
							if (hit != 0)
							{
								*hit = RayHit(
									ray,
									t,
									intersection,
									clamp(vec2((normal.x + 1.0f) / 2.0f, (normal.y + 1.0f) / 2.0f), vec2(0.0f), vec2(1.0f)),
									normal,
									tangent,
									binormal,
									this);
							}

							return true;
						}
					}
				}
			}

			return false;
		}

		RAY_API const int Sphere::elements() const
		{
			return 0;
		}
		RAY_API const int Sphere::components() const
		{
			return 0;
		}
		RAY_API const void* Sphere::buffer() const
		{
			return 0;
		}

	}
}