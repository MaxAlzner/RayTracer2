#ifndef RAY_MESHFILTER_H
#define RAY_MESHFILTER_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API MeshFilter : public Component
		{
		public:

			inline MeshFilter() :
				Component("MeshFilter"),
				shape(0) {}
			inline MeshFilter(Shapes::TraceShape* shape) :
				Component("MeshFilter"),
				shape(shape) {}
			inline ~MeshFilter() {}

			Shapes::TraceShape* shape;

		};

	}
}

#endif