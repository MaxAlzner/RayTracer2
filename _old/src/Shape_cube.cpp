
#include "../include/Ray_main.h"

#ifdef SHAPE_CUBE_H_
RAY_BEGIN
SHAPE_BEGIN

Cube::Cube()
{
	this->width = 1.0f;
}
Cube::Cube(float width)
{
	this->width = width;
}
Cube::~Cube()
{
}

void Cube::build()
{
	Shape::build();
}
void Cube::unpack()
{
	Shape::unpack();
}

bool Cube::hitByRay(Ray& ray, RayHit& hit)
{
	float hw = this->width / 2.0f;
	vec3 p0 = this->transform->position - hw;
	vec3 p1 = this->transform->position + hw;
	float x0 = p0.x;
	float y0 = p0.y;
	float z0 = p0.z;
	float x1 = p1.x;
	float y1 = p1.y;
	float z1 = p1.z;
	float ox = ray.origin.x;
	float oy = ray.origin.y;
	float oz = ray.origin.z;
	float dx = ray.direction.x;
	float dy = ray.direction.y;
	float dz = ray.direction.z;

	if (x0 > x1) Swap(x0, x1);
	if (y0 > y1) Swap(y0, y1);
	if (z0 > z1) Swap(z0, z1);

	float txmin, tymin, tzmin, txmax, tymax, tzmax;

	float a = 1.0f / dx;
	if (a >= 0.0f)
	{
		txmin = (x0 - ox) * a;
		txmax = (x1 - ox) * a;
	}
	else
	{
		txmin = (x1 - ox) * a;
		txmax = (x0 - ox) * a;
	}
	float b = 1.0f / dy;
	if (b >= 0.0f)
	{
		tymin = (y0 - oy) * b;
		tymax = (y1 - oy) * b;
	}
	else
	{
		tymin = (y1 - oy) * b;
		tymax = (y0 - oy) * b;
	}
	float c = 1.0f / dz;
	if (c >= 0.0f)
	{
		tzmin = (z0 - oz) * c;
		tzmax = (z1 - oz) * c;
	}
	else
	{
		tzmin = (z1 - oz) * c;
		tzmax = (z0 - oz) * c;
	}

	float t0, t1;
	int facein, faceout;

	if (txmin > tymin)
	{
		t0 = txmin;
		facein = (a >= 0.0f) ? 0 : 3;
	}
	else
	{
		t0 = tymin;
		facein = (b >= 0.0f) ? 1 : 4;
	}

	if (tzmin > t0)
	{
		t0 = tzmin;
		facein = (c >= 0.0f) ? 2 : 5;
	}


	if (txmax < tymax)
	{
		t1 = txmax;
		faceout = (a >= 0.0f) ? 3 : 0;
	}
	else
	{
		t1 = tymax;
		faceout = (b >= 0.0f) ? 4 : 1;
	}

	if (tzmax < t1)
	{
		t1 = tzmax;
		faceout = (c >= 0.0f) ? 5 : 2;
	}


	float kEpsilon = 1.0f;
	float t = 0.0f;
	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon) t = t0;
		else t = t1;

		if (ray.length > 0.0f && t > ray.length) return false;

		vec3 intersection = ray.origin + (ray.direction * t);
		vec3 normal;

		switch (facein)
		{
		case 0:
			normal = vec3(-1.0f, 0.0f, 0.0f);
			break;
		case 1:
			normal = vec3(0.0f, -1.0f, 0.0f);
			break;
		case 2:
			normal = vec3(0.0f, 0.0f, -1.0f);
			break;
		case 3:
			normal = vec3(1.0f, 0.0f, 0.0f);
			break;
		case 4:
			normal = vec3(0.0f, 1.0f, 0.0f);
			break;
		case 5:
			normal = vec3(0.0f, 0.0f, 1.0f);
			break;
		default:
			break;
		}

		if (dot(ray.direction, normal) > 1.0f) return false;

		float u, v;
		float width = abs(p1.x - p0.x);
		float height = abs(p1.y - p0.y);
		float depth = abs(p1.z - p0.z);
		vec3 toEdge;
		if (facein < 3)
		{
			toEdge = normalize(p0 - intersection);

			if (facein == 0)
			{
				u = abs(toEdge.z) / (depth);
				v = abs(toEdge.y) / (height);
			}
			else if (facein == 1)
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.z) / (depth);
			}
			else
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.y) / (height);
			}
		}
		else
		{
			toEdge = normalize(p1 - intersection);

			if (facein == 3)
			{
				u = abs(toEdge.z) / (depth);
				v = abs(toEdge.y) / (height);
			}
			else if (facein == 4)
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.z) / (depth);
			}
			else
			{
				u = abs(toEdge.x) / (width);
				v = abs(toEdge.y) / (height);
			}
		}
		
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