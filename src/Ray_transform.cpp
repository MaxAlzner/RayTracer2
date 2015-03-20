
#include "../include/Ray_main.h"

#ifdef RAY_TRANSFORM_H_
RAY_BEGIN

Transform::Transform()
{
	//memset(this, 0, sizeof(Transform));
}
Transform::~Transform()
{
}

void Transform::build()
{
	this->zero();
}
void Transform::unpack()
{
}
	
void Transform::setTranslationX(float v)
{
	this->translation.x = v;
}
void Transform::setTranslationY(float v)
{
	this->translation.y = v;
}
void Transform::setTranslationZ(float v)
{
	this->translation.z = v;
}
void Transform::setRotationX(float v)
{
	this->rotation.x = v;
}
void Transform::setRotationY(float v)
{
	this->rotation.y = v;
}
void Transform::setRotationZ(float v)
{
	this->rotation.z = v;
}
void Transform::setScaleX(float v)
{
	this->scaled.x = v;
}
void Transform::setScaleY(float v)
{
	this->scaled.y = v;
}
void Transform::setScaleZ(float v)
{
	this->scaled.z = v;
}
void Transform::setTranslation(float x, float y, float z)
{
	this->translation.x = x;
	this->translation.y = y;
	this->translation.z = z;
}
void Transform::setRotation(float x, float y, float z)
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;

	mod(this->rotation, 360.0f);
}
void Transform::setScale(float x, float y, float z)
{
	this->scaled.x = x;
	this->scaled.y = y;
	this->scaled.z = z;
}

void Transform::translate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;
	
	this->translation.x += x;
	this->translation.y += y;
	this->translation.z += z;
}
void Transform::rotate(float x, float y, float z)
{
	if (x == 0.0f && y == 0.0f && z == 0.0f) return;

	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;

	mod(this->rotation, 360.0f);
}
void Transform::scale(float x, float y, float z)
{
	if (x == 1.0f && y == 1.0f && z == 1.0f) return;
	
	this->scaled.x *= x;
	this->scaled.y *= y;
	this->scaled.z *= z;
}
void Transform::zero()
{
	this->translation = vec3(0.0f, 0.0f, 0.0f);
	this->rotation =    vec3(0.0f, 0.0f, 0.0f);
	this->scaled =      vec3(1.0f, 1.0f, 1.0f);
	this->right =       vec3(1.0f, 0.0f, 0.0f);
	this->up =          vec3(0.0f, 1.0f, 0.0f);
	this->forward =     vec3(0.0f, 0.0f, 1.0f);
	this->space =       mat4(1.0f);
	this->spaceNormal = mat3(1.0f);
}

void Transform::lookAt(float x, float y, float z)
{
}

void Transform::recalculate()
{
	this->space = mat4(1.0f);
#if 0
	if (this->root->parent != NULL)
	{
		this->space *= rotate(this->root->parent->transform->rotation.x, vec3(1.0f, 0.0f, 0.0f));
		this->space *= rotate(this->root->parent->transform->rotation.y, vec3(0.0f, 1.0f, 0.0f));
		this->space *= rotate(this->root->parent->transform->rotation.z, vec3(0.0f, 0.0f, 1.0f));
	}
#endif
	this->space *= glm::rotate(this->rotation.x, vec3(1.0f, 0.0f, 0.0f));
	this->space *= glm::rotate(this->rotation.y, vec3(0.0f, 1.0f, 0.0f));
	this->space *= glm::rotate(this->rotation.z, vec3(0.0f, 0.0f, 1.0f));
	this->spaceNormal = mat3(this->space);

	this->position = this->translation;
#if 0
	if (this->root->parent != NULL)
	{
		this->position += this->root->parent->transform->translation;
	}
#endif
	
	this->right =   normalize(mul(vec3(1.0f, 0.0f, 0.0f), this->spaceNormal));
	this->up =      normalize(mul(vec3(0.0f, 1.0f, 0.0f), this->spaceNormal));
	this->forward = normalize(mul(vec3(0.0f, 0.0f, 1.0f), this->spaceNormal));

	this->transformation = mat4(1.0f);
#if 0
	if (this->root->parent != NULL)
	{
		this->transformation *= translate(this->root->parent->transform->translation);
		this->transformation *= rotate(this->root->parent->transform->rotation.x, vec3(1.0f, 0.0f, 0.0f));
		this->transformation *= rotate(this->root->parent->transform->rotation.y, vec3(0.0f, 1.0f, 0.0f));
		this->transformation *= rotate(this->root->parent->transform->rotation.z, vec3(0.0f, 0.0f, 1.0f));
	}
#endif
	this->transformation *= glm::translate(this->translation);
	this->transformation *= glm::rotate(this->rotation.x, vec3(1.0f, 0.0f, 0.0f));
	this->transformation *= glm::rotate(this->rotation.y, vec3(0.0f, 1.0f, 0.0f));
	this->transformation *= glm::rotate(this->rotation.z, vec3(0.0f, 0.0f, 1.0f));
	this->transformation *= glm::scale(this->scaled);
}

RAY_END
#endif