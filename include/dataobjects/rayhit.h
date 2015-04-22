#ifndef RAY_RAYHIT_H
#define RAY_RAYHIT_H

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		class RAY_API RayHit
		{
		public:

			inline RayHit() :
				intersection(0.0f),
				distance(FLT_MAX),
				texcoord(0.0f),
				normal(0.0f, 0.0f, 1.0f),
				tangent(1.0f, 0.0f, 0.0f),
				binormal(0.0f, 1.0f, 0.0f),
				shape(0) {}
			inline RayHit(
				const ray& r,
				const float distance,
				const vec3& intersection,
				const vec2& texcoord,
				const vec3& normal,
				const vec3& tangent,
				const vec3& binormal,
				const Shapes::TraceShape* shape
				) :
				ray(r),
				distance(distance),
				intersection(intersection),
				texcoord(texcoord),
				normal(normal),
				tangent(tangent),
				binormal(binormal),
				shape(shape) {}
			inline RayHit(const RayHit& hit) :
				ray(hit.ray),
				distance(hit.distance),
				intersection(hit.intersection),
				texcoord(hit.texcoord),
				normal(hit.normal),
				tangent(hit.tangent),
				binormal(hit.binormal),
				shape(hit.shape) {}
			inline ~RayHit() {}

			inline void operator=(const RayHit& rayhit)
			{
				this->ray = rayhit.ray;
				this->distance = rayhit.distance;
				this->intersection = rayhit.intersection;
				this->texcoord = rayhit.texcoord;
				this->normal = rayhit.normal;
				this->tangent = rayhit.tangent;
				this->binormal = rayhit.binormal;
				this->shape = rayhit.shape;
			}

			ray ray;
			float distance;
			vec3 intersection;
			vec2 texcoord;
			vec3 normal;
			vec3 tangent;
			vec3 binormal;
			const Shapes::TraceShape* shape;

		};

	}
}

#endif