
#include "../include/Ray_main.h"

#ifdef SHAPE_SPHERE_H_
RAY_BEGIN
SHAPE_BEGIN

InvSphere::InvSphere()
{
	this->radius = 1.0f;
}
InvSphere::InvSphere(float radius)
{
	this->radius = radius;
}
InvSphere::~InvSphere()
{
}

void InvSphere::build()
{
	Shape::build();
}
void InvSphere::unpack()
{
	Shape::unpack();
}

bool InvSphere::hitByRay(Ray& ray, RayHit& hit)
{
	float a = dot(ray.direction, ray.direction);
	float b = dot(((ray.origin - this->transform->position) * 2.0f), ray.direction);
	float c = dot((ray.origin - this->transform->position), (ray.origin - this->transform->position)) - (this->radius * this->radius);
	float d = (b * b) - (4.0f * a * c);

	if (d >= 0.0f)
	{
		float e = sqrt(d);

		float t1 = (-b - e) / (2.0f * a);
		float t2 = (-b + e) / (2.0f * a);

		if (t1 < 0.0f || t2 < 0.0f) return false;

		vec3 intersection;
		float t;
		if (t1 > t2)
		{
			intersection = ray.origin + (ray.direction * t1);
			t = t1;
		}
		else
		{
			intersection = ray.origin + (ray.direction * t2);
			t = t2;
		}

		if (ray.length > 0.0f && t > ray.length) return false;

		vec3 normal = normalize(intersection - this->transform->position);

		float u = (normal.x + 1.0f) / 2.0f;
		float v = (normal.y + 1.0f) / 2.0f;

		hit.ray = ray;
		hit.intersection = intersection;
		hit.traveled = t;
		hit.normal = normal;
		hit.texcoord = vec2(u, v);
		hit.surface = this;

		return true;
	}
	
	return false;
}

SHAPE_END
RAY_END
#endif