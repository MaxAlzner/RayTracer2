#ifndef RAY_AXISCUBE_H
#define RAY_AXISCUBE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		class RAY_API AxisCube : public TraceShape
		{
		public:

			AxisCube() : TraceShape() {}
			~AxisCube() {}

			void build();

			bool hitByRay(const ray& ray, const Object::Mesh::transformation<float>& trans, DataObjects::RayHit* hit);

			const int elements() const;
			const int components() const;
			const void* buffer() const;

		};

	}
}

#endif