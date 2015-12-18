
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Shapes
	{
		using namespace DataObjects;

		RAY_API void OctPartitionShape::build()
		{
			this->_base = new OctPartition;
			this->_base->subsection0 = new OctPartition(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f));
			this->_base->subsection1 = new OctPartition(vec3(0.0f, 0.5f, 0.5f), vec3(0.5f, 1.0f, 1.0f));
			this->_base->subsection2 = new OctPartition(vec3(0.5f, 0.5f, 0.0f), vec3(1.0f, 1.0f, 0.5f));
			this->_base->subsection3 = new OctPartition(vec3(0.0f, 0.5f, 0.0f), vec3(0.5f, 1.0f, 0.5f));
			this->_base->subsection4 = new OctPartition(vec3(0.5f, 0.0f, 0.5f), vec3(1.0f, 0.5f, 1.0f));
			this->_base->subsection5 = new OctPartition(vec3(0.0f, 0.0f, 0.5f), vec3(0.5f, 0.5f, 1.0f));
			this->_base->subsection6 = new OctPartition(vec3(0.5f, 0.0f, 0.0f), vec3(1.0f, 0.5f, 0.5f));
			this->_base->subsection7 = new OctPartition(vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
		}
		RAY_API void OctPartitionShape::dispose()
		{
			if (this->_base != 0)
			{
				this->_base->clear();
				delete this->_base;
				this->_base = 0;
			}
		}

		RAY_API void OctPartitionShape::putFace(const int index, const ivec3& face)
		{
			vec3 bounds = this->_max - this->_min;
			vec3 center = bounds * 0.5f;
			//vec3 v = (this->getVertex(face.x) + this->getVertex(face.y) + this->getVertex(face.z)) / 3.0f;

			ivec3* read = this->faceIndices + index;
			*read = face;

			vec3 v0 = (vec3(this->getVertex(face.x)) - this->_min) / bounds;
			vec3 v1 = (vec3(this->getVertex(face.y)) - this->_min) / bounds;
			vec3 v2 = (vec3(this->getVertex(face.z)) - this->_min) / bounds;

			OctPartition* a = this->_base->get(v0);
			OctPartition* b = this->_base->get(v1);
			OctPartition* c = this->_base->get(v2);

			if (a != 0)
			{
				a->faces.add(read);
			}

			if (b != 0 && b != a)
			{
				b->faces.add(read);
			}

			if (c != 0 && c != b && c != a)
			{
				c->faces.add(read);
			}
		}
		RAY_API void OctPartitionShape::putVertex(const int index, const vec4& v)
		{
			Shape::putVertex(index, v);
			this->_min.x = min(this->_min.x, v.x);
			this->_min.y = min(this->_min.y, v.y);
			this->_min.z = min(this->_min.z, v.z);
			this->_max.x = max(this->_max.x, v.x);
			this->_max.y = max(this->_max.y, v.y);
			this->_max.z = max(this->_max.z, v.z);
		}

		RAY_API bool OctPartitionShape::hitByRay(const ray& ray, const transformation<float>& trans, RayHit* hit)
		{
#if 0
			bool didHit = false;
			for (int i = 0; i < 8; i++)
			{
				OctPartition* partition = this->_base->subsections[i];
				if (partition != 0)
				{
					vec3 bounds = this->_max - this->_min;
					vec3 min = ((this->_min + (bounds * partition->p0)) * trans.scale) + trans.translation;
					vec3 max = ((this->_min + (bounds * partition->p1)) * trans.scale) + trans.translation;
					if (this->_sectionHitByRay(ray, min, max))
					{
						for (Iterator<ivec3*> i = partition->faces.iterator(); i.inside(); i.next())
						{
							ivec3* face = i.current();
							RayHit faceHit;
							if (face != 0 && this->_faceHitByRay(ray, trans, *face, &faceHit))
							{
								if (hit != 0 && hit->distance > faceHit.distance)
								{
									*hit = faceHit;
								}

								didHit = true;
							}
						}
					}
				}
			}

			return didHit;
#else
			bool didHit = false;
			for (int n = 0; n < this->faceIndices.elements; n++)
			{
				ivec3 face = this->faceIndices[n];
				vec3 va = (vec3(this->vertices[face.x]) * trans.scale * trans.space) + trans.translation;
				vec3 vb = (vec3(this->vertices[face.y]) * trans.scale * trans.space) + trans.translation;
				vec3 vc = (vec3(this->vertices[face.z]) * trans.scale * trans.space) + trans.translation;

#if 1
				vec3 faceNormal = glm::normalize(cross(vb - va, vc - vb));
				if (dot(ray.direction, faceNormal) > 0.0f)
				{
					continue;
				}
#endif

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
						if (hit != 0 && hit->distance > t)
						{
							*hit = RayHit(
								ray,
								t,
								ray.origin + (ray.direction * t),
								clamp(vec2((alpha * ta) + (beta * tb) + (gamma * tc)), vec2(0.0f), vec2(1.0f)),
								glm::normalize((alpha * this->normals[face.x]) + (beta * this->normals[face.y]) + (gamma * this->normals[face.z])),
								glm::normalize((alpha * this->tangents[face.x]) + (beta * this->tangents[face.y]) + (gamma * this->tangents[face.z])),
								glm::normalize((alpha * this->binormals[face.x]) + (beta * this->binormals[face.y]) + (gamma * this->binormals[face.z])),
								this);
						}

						didHit = true;
					}
				}
			}

			return didHit;
#endif
		}

		RAY_API bool OctPartitionShape::_sectionHitByRay(const ray& ray, const vec3& min, const vec3& max)
		{
			float a = 1.0f / ray.direction.x;
			float b = 1.0f / ray.direction.y;
			float c = 1.0f / ray.direction.z;

			float txmin = a >= 0.0f ? (min.x - ray.origin.x) * a : (max.x - ray.origin.x) * a;
			float tymin = b >= 0.0f ? (min.y - ray.origin.y) * b : (max.y - ray.origin.y) * b;
			float tzmin = c >= 0.0f ? (min.z - ray.origin.z) * c : (max.z - ray.origin.z) * c;
			float txmax = a >= 0.0f ? (max.x - ray.origin.x) * a : (min.x - ray.origin.x) * a;
			float tymax = b >= 0.0f ? (max.y - ray.origin.y) * b : (min.y - ray.origin.y) * b;
			float tzmax = c >= 0.0f ? (max.z - ray.origin.z) * c : (min.z - ray.origin.z) * c;

			float t0 = txmin > tymin ? txmin : tymin;
			float t1 = txmax < tymax ? txmax : tymax;

			if (tzmin > t0)
			{
				t0 = tzmin;
			}

			if (tzmax < t1)
			{
				t1 = tzmax;
			}

			float kEpsilon = 1.0f;
			if (t0 < t1 && t1 > kEpsilon)
			{
				float t = t0 > kEpsilon ? t0 : t1;

				if (t <= ray.length)
				{
					//vec3 intersection = ray.origin + (ray.direction * t);

					return true;
				}
			}

			return false;
		}
		RAY_API bool OctPartitionShape::_faceHitByRay(const ray& ray, const transformation<float>& trans, const ivec3& face, RayHit* hit)
		{
			vec3 va = (vec3(this->vertices[face.x]) * trans.scale * trans.space) + trans.translation;
			vec3 vb = (vec3(this->vertices[face.y]) * trans.scale * trans.space) + trans.translation;
			vec3 vc = (vec3(this->vertices[face.z]) * trans.scale * trans.space) + trans.translation;

#if 0
			vec3 faceNormal = normalize(cross(vb - va, vc - vb));
			if (dot(ray.direction, faceNormal) > 0.0f)
			{
				continue;
			}
#endif

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
					if (hit != 0 && hit->distance > t)
					{
						*hit = RayHit(
							ray,
							t,
							ray.origin + (ray.direction * t),
							clamp(vec2((alpha * this->texcoords[face.x]) + (beta * this->texcoords[face.y]) + (gamma * this->texcoords[face.z])), vec2(0.0f), vec2(1.0f)),
							glm::normalize((alpha * this->normals[face.x]) + (beta * this->normals[face.y]) + (gamma * this->normals[face.z])),
							glm::normalize((alpha * this->tangents[face.x]) + (beta * this->tangents[face.y]) + (gamma * this->tangents[face.z])),
							glm::normalize((alpha * this->binormals[face.x]) + (beta * this->binormals[face.y]) + (gamma * this->binormals[face.z])),
							this);
					}

					return true;
				}
			}

			return false;
		}

		RAY_API void OctPartition::clear()
		{
			this->faces.clear();
			for (int i = 0; i < 8; i++)
			{
				if (this->subsections[i] != 0)
				{
					delete this->subsections[i];
					this->subsections[i] = 0;
				}
			}
		}

		RAY_API OctPartition* OctPartition::get(const vec3& p)
		{
			vec3 center = (this->p1 - this->p0) + this->p0;
			if (p.y >= center.y)
			{
				if (p.z >= center.z)
				{
					if (p.x >= center.x)
					{
						return this->subsection0;
					}
					else
					{
						return this->subsection1;
					}
				}
				else
				{
					if (p.x >= center.x)
					{
						return this->subsection2;
					}
					else
					{
						return this->subsection3;
					}
				}
			}
			else
			{
				if (p.z >= center.z)
				{
					if (p.x >= center.x)
					{
						return this->subsection4;
					}
					else
					{
						return this->subsection5;
					}
				}
				else
				{
					if (p.x >= center.x)
					{
						return this->subsection6;
					}
					else
					{
						return this->subsection7;
					}
				}
			}
		}

	}
}