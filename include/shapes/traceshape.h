#ifndef RAY_TRACESHAPE_H
#define RAY_TRACESHAPE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		class RAY_API TraceShape : public Shape
		{
		public:

			TraceShape() : Shape() {}
			~TraceShape() {}

			virtual bool hitByRay(const ray& ray, const medialoader::Mesh::transformation<float>& trans, DataObjects::RayHit* hit) = 0;

		};

	}
}

#endif