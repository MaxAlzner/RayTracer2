#ifndef RAY_AXISCUBE_H
#define RAY_AXISCUBE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		class RAY_API AxisCube : public Object::Mesh::Shape
		{
		public:

			AxisCube() {}
			~AxisCube() {}

			void build();
			void dispose();

			bool hitByRay(const ray& ray, const Object::Mesh::transformation<float>& trans, rayhit* hit);

			const int elements() const;
			const int components() const;
			const void* buffer() const;

		};

	}
}

#endif