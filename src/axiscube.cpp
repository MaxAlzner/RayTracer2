
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace Object::Mesh;

		RAY_API void AxisCube::build()
		{
			this->vertices = component<vec4>(new vec4[2], 2, 0);
			this->vertices[0] = vec4(-1.0f, -1.0f, -1.0f, 1.0f);
			this->vertices[1] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			this->normals = component<vec3>(new vec3[6], 6, 0);
			this->normals[0] = vec3(-1.0f, 0.0f, 0.0f);
			this->normals[1] = vec3(0.0f, -1.0f, 0.0f);
			this->normals[2] = vec3(0.0f, 0.0f, -1.0f);
			this->normals[3] = vec3(1.0f, 0.0f, 0.0f);
			this->normals[4] = vec3(0.0f, 1.0f, 0.0f);
			this->normals[5] = vec3(0.0f, 0.0f, 1.0f);
		}
		RAY_API void AxisCube::dispose()
		{
			if (this->vertices.buffer != 0)
			{
				delete[] this->vertices.buffer;
				this->vertices = component<vec4>();
			}

			if (this->normals.buffer != 0)
			{
				delete[] this->normals.buffer;
				this->normals = component<vec3>();
			}
		}

		RAY_API bool AxisCube::hitByRay(const ray& ray, const transformation<float>& trans, rayhit* hit)
		{
			vec3 p0 = (vec3(this->vertices[0]) * trans.scale) + trans.translation;
			vec3 p1 = (vec3(this->vertices[1]) * trans.scale) + trans.translation;

			if (p0.x > p1.x)
			{
				Math::swap(p0.x, p1.x);
			}

			if (p0.y > p1.y)
			{
				Math::swap(p0.y, p1.y);
			}

			if (p0.z > p1.z)
			{
				Math::swap(p0.z, p1.z);
			}

			float txmin, tymin, tzmin, txmax, tymax, tzmax;

			float a = 1.0f / ray.direction.x;
			if (a >= 0.0f)
			{
				txmin = (p0.x - ray.origin.x) * a;
				txmax = (p1.x - ray.origin.x) * a;
			}
			else
			{
				txmin = (p1.x - ray.origin.x) * a;
				txmax = (p0.x - ray.origin.x) * a;
			}

			float b = 1.0f / ray.direction.y;
			if (b >= 0.0f)
			{
				tymin = (p0.y - ray.origin.y) * b;
				tymax = (p1.y - ray.origin.y) * b;
			}
			else
			{
				tymin = (p1.y - ray.origin.y) * b;
				tymax = (p0.y - ray.origin.y) * b;
			}

			float c = 1.0f / ray.direction.z;
			if (c >= 0.0f)
			{
				tzmin = (p0.z - ray.origin.z) * c;
				tzmax = (p1.z - ray.origin.z) * c;
			}
			else
			{
				tzmin = (p1.z - ray.origin.z) * c;
				tzmax = (p0.z - ray.origin.z) * c;
			}

			float t0, t1;
			int facein, faceout;

			if (txmin > tymin)
			{
				t0 = txmin;
				facein = (a >= 0.0f) ? 0 : 3;
			}
			else
			{
				t0 = tymin;
				facein = (b >= 0.0f) ? 1 : 4;
			}

			if (tzmin > t0)
			{
				t0 = tzmin;
				facein = (c >= 0.0f) ? 2 : 5;
			}


			if (txmax < tymax)
			{
				t1 = txmax;
				faceout = (a >= 0.0f) ? 3 : 0;
			}
			else
			{
				t1 = tymax;
				faceout = (b >= 0.0f) ? 4 : 1;
			}

			if (tzmax < t1)
			{
				t1 = tzmax;
				faceout = (c >= 0.0f) ? 5 : 2;
			}


			float kEpsilon = 1.0f;
			if (t0 < t1 && t1 > kEpsilon)
			{
				float t = t0 > kEpsilon ? t0: t1;

				if (t <= ray.length)
				{
					vec3 intersection = ray.origin + (ray.direction * t);
					vec3 normal = this->normals[facein];

					float width = abs(p1.x - p0.x);
					float height = abs(p1.y - p0.y);
					float depth = abs(p1.z - p0.z);
					vec3 toInnerEdge = p0 - intersection;
					vec3 toOuterEdge = p1 - intersection;
					vec2 texcoord;
					switch (facein)
					{
					case 0:
						texcoord = vec2(abs(toOuterEdge.z) / (depth), abs(toInnerEdge.y) / (height));
						break;
					case 1:
						texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toOuterEdge.z) / (depth));
						break;
					case 2:
						texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toInnerEdge.y) / (height));
						break;
					case 3:
						texcoord = vec2(abs(toInnerEdge.z) / (depth), abs(toInnerEdge.y) / (height));
						break;
					case 4:
						texcoord = vec2(abs(toInnerEdge.x) / (width), abs(toInnerEdge.z) / (depth));
						break;
					case 5:
						texcoord = vec2(abs(toOuterEdge.x) / (width), abs(toInnerEdge.y) / (height));
						break;
					default:
						break;
					}

					if (hit != 0)
					{
						*hit = rayhit(
							ray,
							t,
							intersection,
							texcoord,
							normal,
							this);
					}

					return true;
				}
			}

			return false;
		}

		RAY_API const int AxisCube::elements() const
		{
			return 2;
		}
		RAY_API const int AxisCube::components() const
		{
			return 2;
		}
		RAY_API const void* AxisCube::buffer() const
		{
			return this->vertices.buffer;
		}

	}
}