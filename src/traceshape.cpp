
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace Object::Mesh;
		using namespace DataObjects;

		RAY_API bool TraceShape::hitByRay(const ray& ray, const transformation<float>& trans, RayHit* hit)
		{
			for (int n = 0; n < this->faces.elements; n++)
			{
				ivec3 face = this->faces[n];
				vec3 va = vec3(this->vertices[face.x]);
				vec3 vb = vec3(this->vertices[face.y]);
				vec3 vc = vec3(this->vertices[face.z]);

				va *= trans.scale;
				vb *= trans.scale;
				vc *= trans.scale;
				va = va * trans.space;
				vb = vb * trans.space;
				vc = vc * trans.space;
				va += trans.translation;
				vb += trans.translation;
				vc += trans.translation;

				vec3 faceNormal = Math::normalize(Math::cross(vb - va, vc - vb));
				if (Math::dot(ray.direction, faceNormal) > 0.0f)
				{
					continue;
				}

				vec2 ta = this->texcoords[face.x];
				vec2 tb = this->texcoords[face.y];
				vec2 tc = this->texcoords[face.z];

				float a = va.x - vb.x;
				float b = va.x - vc.x;
				float c = ray.direction.x;
				float d = va.x - ray.origin.x;
				float e = va.y - vb.y;
				float f = va.y - vc.y;
				float g = ray.direction.y;
				float h = va.y - ray.origin.y;
				float i = va.z - vb.z;
				float j = va.z - vc.z;
				float k = ray.direction.z;
				float l = va.z - ray.origin.z;

				float beta =
					((d * ((f * k) - (g * j))) + (b * ((g * l) - (h * k))) + (c * ((h * j) - (f * l)))) /
					((a * ((f * k) - (g * j))) + (b * ((g * i) - (e * k))) + (c * ((e * j) - (f * i))));
				float gamma =
					((a * ((h * k) - (g * l))) + (d * ((g * i) - (e * k))) + (c * ((e * l) - (h * i)))) /
					((a * ((f * k) - (g * j))) + (b * ((g * i) - (e * k))) + (c * ((e * j) - (f * i))));
				float alpha = 1.0f - (beta + gamma);

				if (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f)
				{
					float t =
						(a * (f * l - h * j) + b * (h * i - e * l) + d * (e * j - f * i)) /
						(a * (f * k - g * j) + b * (g * i - e * k) + c * (e * j - f * i));

					if (t <= ray.length)
					{
						if (hit != 0)
						{
							*hit = RayHit(
								ray,
								t,
								ray.origin + (ray.direction * t),
								Math::clamp(vec2((alpha * ta) + (beta * tb) + (gamma * tc)), 0.0f, 1.0f),
								Math::normalize((alpha * this->normals[face.x]) + (beta * this->normals[face.y]) + (gamma * this->normals[face.z])),
								Math::normalize((alpha * this->tangents[face.x]) + (beta * this->tangents[face.y]) + (gamma * this->tangents[face.z])),
								Math::normalize((alpha * this->binormals[face.x]) + (beta * this->binormals[face.y]) + (gamma * this->binormals[face.z])),
								this);
						}

						return true;
					}
				}
			}

			return false;
		}

	}
}