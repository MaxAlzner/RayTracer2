#ifndef RAY_TRACESHAPE_H
#define RAY_TRACESHAPE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		class RAY_API TraceShape : public Object::Mesh::Shape
		{
		public:

			TraceShape() : Shape() {}
			~TraceShape() {}

			virtual bool hitByRay(const ray& ray, const Mesh::transformation<float>& trans, DataObjects::RayHit* hit) = 0;

		};

	}
}

#endif