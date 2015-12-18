
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{

		RAY_API inline void Transform::recalculate()
		{
			this->space = mat4(1.0f);
			this->space *= glm::rotateX(glm::vec3(1.0f, 0.0f, 0.0f), this->rotation.x);
			this->space *= glm::rotateY(glm::vec3(0.0f, 1.0f, 0.0f), this->rotation.y);
			this->space *= glm::rotateZ(glm::vec3(0.0f, 0.0f, 1.0f), this->rotation.z);

			this->transformation = mat4(1.0f);
			this->transformation *= translate(this->position);
			this->transformation *= glm::rotateX(glm::vec3(1.0f, 0.0f, 0.0f), this->rotation.x);
			this->transformation *= glm::rotateY(glm::vec3(0.0f, 1.0f, 0.0f), this->rotation.y);
			this->transformation *= glm::rotateZ(glm::vec3(0.0f, 0.0f, 1.0f), this->rotation.z);
			this->transformation *= this->space;
			this->transformation *= glm::scale(this->scale);

			mat3 spaceNormal = mat3(this->space);
			this->right = normalize(vec3(1.0f, 0.0f, 0.0f) * spaceNormal);
			this->up = normalize(vec3(0.0f, 1.0f, 0.0f) * spaceNormal);
			this->forward = normalize(vec3(0.0f, 0.0f, 1.0f) * spaceNormal);
		}
		RAY_API inline void Transform::zero()
		{
			this->transformation = mat4(1.0f);
			this->space = mat4(1.0f);
			this->position = vec3(0.0f);
			this->rotation = vec3(0.0f);
			this->scale = vec3(1.0f);
			this->right = vec3(1.0f, 0.0f, 0.0f);
			this->up = vec3(0.0f, 1.0f, 0.0f);
			this->forward = vec3(0.0f, 0.0f, 1.0f);
		}

		RAY_API inline void Transform::look(const vec3& focus)
		{
			vec3 to = normalize(focus - this->position);
		}

	}
}