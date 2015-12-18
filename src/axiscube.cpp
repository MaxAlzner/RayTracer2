
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace DataObjects;

		RAY_API void AxisCube::build()
		{
			this->_size = (sizeof(float) * 8) + (sizeof(float) * 18) + (sizeof(float) * 18) + (sizeof(float) * 18);
			this->_buffer = malloc(this->_size);
			this->vertices = component<vec4>((vec4*)this->_buffer, 2, 0);
			this->vertices[0] = vec4(-1.0f, -1.0f, -1.0f, 1.0f);
			this->vertices[1] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			this->normals = component<vec3>((vec3*)(((float*)this->_buffer) + 8), 6, 0);
			this->normals[0] = vec3(-1.0f, 0.0f, 0.0f);
			this->normals[1] = vec3(0.0f, -1.0f, 0.0f);
			this->normals[2] = vec3(0.0f, 0.0f, -1.0f);
			this->normals[3] = vec3(1.0f, 0.0f, 0.0f);
			this->normals[4] = vec3(0.0f, 1.0f, 0.0f);
			this->normals[5] = vec3(0.0f, 0.0f, 1.0f);
			this->tangents = component<vec3>((vec3*)(((float*)this->_buffer) + 26), 6, 0);
			this->tangents[0] = vec3(0.0f, 0.0f, -1.0f);
			this->tangents[1] = vec3(1.0f, 0.0f, 0.0f);
			this->tangents[2] = vec3(1.0f, 0.0f, 0.0f);
			this->tangents[3] = vec3(0.0f, 0.0f, 1.0f);
			this->tangents[4] = vec3(1.0f, 0.0f, 0.0f);
			this->tangents[5] = vec3(1.0f, 0.0f, 0.0f);
			this->binormals = component<vec3>((vec3*)(((float*)this->_buffer) + 44), 6, 0);
			this->binormals[0] = vec3(0.0f, -1.0f, 0.0f);
			this->binormals[1] = vec3(0.0f, 0.0f, -1.0f);
			this->binormals[2] = vec3(0.0f, -1.0f, 0.0f);
			this->binormals[3] = vec3(0.0f, 1.0f, 0.0f);
			this->binormals[4] = vec3(0.0f, 0.0f, 1.0f);
			this->binormals[5] = vec3(0.0f, 1.0f, 0.0f);
		}

		RAY_API bool AxisCube::hitByRay(const ray& ray, const transformation<float>& trans, RayHit* hit)
		{
			vec3 p0 = (vec3(this->vertices[0]) * trans.scale) + trans.translation;
			vec3 p1 = (vec3(this->vertices[1]) * trans.scale) + trans.translation;

			if (p0.x > p1.x)
			{
				std::swap(p0.x, p1.x);
			}

			if (p0.y > p1.y)
			{
				std::swap(p0.y, p1.y);
			}

			if (p0.z > p1.z)
			{
				std::swap(p0.z, p1.z);
			}

			float a = 1.0f / ray.direction.x;
			float b = 1.0f / ray.direction.y;
			float c = 1.0f / ray.direction.z;

			float txmin = a >= 0.0f ? (p0.x - ray.origin.x) * a : (p1.x - ray.origin.x) * a;
			float tymin = b >= 0.0f ? (p0.y - ray.origin.y) * b : (p1.y - ray.origin.y) * b;
			float tzmin = c >= 0.0f ? (p0.z - ray.origin.z) * c : (p1.z - ray.origin.z) * c;
			float txmax = a >= 0.0f ? (p1.x - ray.origin.x) * a : (p0.x - ray.origin.x) * a;
			float tymax = b >= 0.0f ? (p1.y - ray.origin.y) * b : (p0.y - ray.origin.y) * b;
			float tzmax = c >= 0.0f ? (p1.z - ray.origin.z) * c : (p0.z - ray.origin.z) * c;

			float t0 = txmin > tymin ? txmin : tymin;
			float t1 = txmax < tymax ? txmax : tymax;

			int facein = txmin > tymin ? ((a >= 0.0f) ? 0 : 3) : ((b >= 0.0f) ? 1 : 4);
			int faceout = txmax < tymax ? ((a >= 0.0f) ? 3 : 0) : ((b >= 0.0f) ? 4 : 1);

			if (tzmin > t0)
			{
				t0 = tzmin;
				facein = (c >= 0.0f) ? 2 : 5;
			}

			if (tzmax < t1)
			{
				t1 = tzmax;
				faceout = (c >= 0.0f) ? 5 : 2;
			}

			float kEpsilon = 1.0f;
			if (t0 < t1 && t1 > kEpsilon)
			{
				float t = t0 > kEpsilon ? t0 : t1;

				if (t <= ray.length)
				{
					vec3 intersection = ray.origin + (ray.direction * t);

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

					vec3 normal = this->normals[facein];
					vec3 tangent = this->tangents[facein];
					vec3 binormal = this->binormals[facein];

					if (dot(normal, ray.direction) < 0.0f)
					{
						if (hit != 0)
						{
							*hit = RayHit(
								ray,
								t,
								intersection,
								texcoord,
								normal,
								tangent,
								binormal,
								this);
						}

						return true;
					}
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