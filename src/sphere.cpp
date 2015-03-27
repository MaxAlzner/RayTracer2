
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace Object::Mesh;

		RAY_API void Sphere::normalize()
		{
			this->radius = 1.0f;
		}

		RAY_API bool Sphere::hitByRay(const ray& ray, const transformation<float>& trans, rayhit* hit)
		{
			vec3 p = (ray.origin - trans.translation);
			float a = Math::dot(ray.direction, ray.direction);
			float b = Math::dot((p * 2.0f), ray.direction);
			float c = Math::dot(p, p) - (this->radius * this->radius);
			float d = (b * b) - (4.0f * a * c);

			if (d >= 0.0f)
			{
				float e = sqrt(d);

				float t0 = (-b - e) / (2.0f * a);
				float t1 = (-b + e) / (2.0f * a);

				if (t0 >= 0.0f && t1 >= 0.0f)
				{
					vec3 intersection = t0 < t1 ?
						ray.origin + (ray.direction * t0) :
						ray.origin + (ray.direction * t1);
					float t = t0 < t1 ? t0 : t1;

					vec3 normal = Math::normalize(intersection - trans.translation);

					if (hit != 0)
					{
						*hit = rayhit(
							ray,
							t,
							intersection,
							Math::clamp(vec2((normal.x + 1.0f) / 2.0f, (normal.y + 1.0f) / 2.0f), 0.0f, 1.0f),
							normal,
							this);
					}

					return true;
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