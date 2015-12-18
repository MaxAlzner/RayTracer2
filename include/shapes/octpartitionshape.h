#ifndef RAY_OCTPARTITIONSHAPE_H
#define RAY_OCTPARTITIONSHAPE_H

namespace RAY_NAMESPACE
{
	namespace Shapes
	{

		struct RAY_API OctPartition;

		class RAY_API OctPartitionShape : public TraceShape
		{
		public:

			OctPartitionShape() :
				TraceShape(),
				_min(0.0f),
				_max(0.0f),
				_base(0) {}
			~OctPartitionShape() {}

			void build();
			void dispose();

			void putFace(const int index, const glm::ivec3& face);
			void putVertex(const int index, const glm::vec4& v);

			bool hitByRay(const ray& ray, const transformation<float>& trans, DataObjects::RayHit* hit);

		protected:

			bool _sectionHitByRay(const ray& ray, const glm::vec3& min, const glm::vec3& max);
			bool _faceHitByRay(const ray& ray, const transformation<float>& trans, const glm::ivec3& face, DataObjects::RayHit* hit);

			glm::vec3 _min;
			glm::vec3 _max;
			OctPartition* _base;

		};

		struct RAY_API OctPartition
		{

			inline OctPartition() :
				p0(0.0f),
				p1(1.0f),
				subsection0(0),
				subsection1(0),
				subsection2(0),
				subsection3(0),
				subsection4(0),
				subsection5(0),
				subsection6(0),
				subsection7(0) {}
			inline OctPartition(const glm::vec3& p0, const glm::vec3& p1) :
				p0(p0),
				p1(p1),
				subsection0(0),
				subsection1(0),
				subsection2(0),
				subsection3(0),
				subsection4(0),
				subsection5(0),
				subsection6(0),
				subsection7(0) {}
			inline ~OctPartition() {}

			inline void clear();

			inline OctPartition* get(const glm::vec3& p);

			glm::vec3 p0;
			glm::vec3 p1;
			List<glm::ivec3*> faces;

			union
			{
				struct
				{
					OctPartition* subsection0;
					OctPartition* subsection1;
					OctPartition* subsection2;
					OctPartition* subsection3;
					OctPartition* subsection4;
					OctPartition* subsection5;
					OctPartition* subsection6;
					OctPartition* subsection7;
				};

				OctPartition* subsections[8];
			};

		};

	}
}

#endif