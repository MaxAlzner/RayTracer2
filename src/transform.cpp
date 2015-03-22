
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{

		RAY_API inline void Transform::recalculate()
		{
			this->space = mat4(1.0f);
			this->space *= Math::rotateX(this->rotation.x);
			this->space *= Math::rotateY(this->rotation.y);
			this->space *= Math::rotateZ(this->rotation.z);

			this->transformation = mat4(1.0f);
			this->transformation *= Math::translate(this->position);
			this->transformation *= Math::rotateX(this->rotation.x);
			this->transformation *= Math::rotateY(this->rotation.y);
			this->transformation *= Math::rotateZ(this->rotation.z);
			this->transformation *= this->space;
			this->transformation *= Math::scale(this->scale);

			mat3 spaceNormal = mat3(this->space);
			this->right = Math::normalize(vec3(1.0f, 0.0f, 0.0f) * spaceNormal);
			this->up = Math::normalize(vec3(0.0f, 1.0f, 0.0f) * spaceNormal);
			this->forward = Math::normalize(vec3(0.0f, 0.0f, 1.0f) * spaceNormal);
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

	}
}