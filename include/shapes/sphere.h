#ifndef RAY_SPHERE_H
#define RAY_SPHERE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		class RAY_API Sphere : public TraceShape
		{
		public:

			Sphere() : TraceShape(), radius(1.0f) {}
			Sphere(float radius) : TraceShape(), radius(radius) {}
			~Sphere() {}

			void normalize();

			bool hitByRay(const ray& ray, const Object::Mesh::transformation<float>& trans, DataObjects::RayHit* hit);

			const int elements() const;
			const int components() const;
			const void* buffer() const;

			float radius;

		};

	}
}

#endif