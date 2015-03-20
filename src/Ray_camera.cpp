
#include "../include/Ray_main.h"

#ifdef RAY_CAMERA_H_
RAY_BEGIN

Camera::Camera()
{
}
Camera::~Camera()
{
}

void Camera::build()
{
	Entity::build();

	this->aperture = vec2(4.0f, 3.0f);
	this->focalDepth = -1.0f;
	this->reflectDepth = 1;
	this->multisampleDepth = 1; 
}
void Camera::unpack()
{
	Entity::unpack();
}

void Camera::adjust()
{
	float x = float(this->aperture.x) / 2.0f;
	float y = float(this->aperture.y) / 2.0f;

	this->viewport.p1 = this->transform->position + (this->transform->right * -x) + (this->transform->up * y);
	this->viewport.p2 = this->transform->position + (this->transform->right * x) + (this->transform->up * y);
	this->viewport.p3 = this->transform->position + (this->transform->right * -x) + (this->transform->up * -y);
	this->viewport.p4 = this->transform->position + (this->transform->right * x) + (this->transform->up * -y);
	this->viewport.px = this->viewport.p2 - this->viewport.p1;
	this->viewport.py = this->viewport.p3 - this->viewport.p1;
	if (focalDepth < 0.0f) this->viewport.focal = this->transform->position;
	else this->viewport.focal = this->transform->position + (this->transform->forward * -this->focalDepth);
}

RayPath* Camera::traceRay(float u, float v, ARRAY<Shape*>& stack)
{
	RayPath* path = new RayPath(this->reflectDepth);
	RayHit hit;
	float zcheck = FLT_MAX;
	for (int i = 0; i < stack.length(); i++)
	{
		Shape* shape = stack[i];
		if (shape == 0) continue;

		Ray ray = this->getRay(u, v);
		RayHit current;
		bool check = shape->hitByRay(ray, current);

		if (check && current.traveled < zcheck)
		{
			hit = current;
			zcheck = current.traveled;
		}
	}

	if (hit.surface == 0) return 0;
	*path += hit;
	return path;
}

Ray Camera::getRay(float u, float v)
{
	vec3 origin = this->viewport.p1 + (this->viewport.px * u) + (this->viewport.py * v);
	vec3 direction;
	if (this->focalDepth < 0.0f) direction = this->transform->forward;
	else direction = normalize(origin - this->viewport.focal);

	return Ray(origin, direction);
}
Ray Camera::getRay(vec2& uv)
{
	return this->getRay(uv.x, uv.y);
}

RAY_END
#endif