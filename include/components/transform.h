#ifndef RAY_TRANSFORM_H
#define RAY_TRANSFORM_H

namespace RAY_NAMESPACE
{
	namespace Components
	{

		class RAY_API Transform : public Component
		{
		public:

			inline Transform() :
				Component("Transform"),
				parent(0) { this->zero(); }
			inline Transform(Transform* parent) :
				Component("Transform"),
				parent(parent != this ? parent : 0) { this->zero(); }
			inline virtual ~Transform() {}

			inline void recalculate();
			inline void zero();

			inline void look(const glm::vec3& focus);

			const Transform* parent;
			glm::mat4 transformation;
			glm::mat4 space;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			glm::vec3 right;
			glm::vec3 up;
			glm::vec3 forward;

		};

	}
}

#endif