#ifndef RAY_RAYHIT_H
#define RAY_RAYHIT_H

namespace RAY_NAMESPACE
{
	namespace Primitives
	{

		class RAY_API RayHit
		{
		public:

			inline RayHit() :
				normal(0.0f, 0.0f, 1.0f),
				material(0) {}
			inline RayHit(const ray& ray, const vec3& intersection, const vec2& texcoord, const vec3& normal, const Components::Material* material) :
				ray(ray),
				intersection(intersection),
				texcoord(texcoord),
				normal(normal),
				material(material) {}
			inline ~RayHit() {}

			ray ray;
			vec3 intersection;
			vec2 texcoord;
			vec3 normal;
			const Components::Material* material;

		};

	}
}

#endif