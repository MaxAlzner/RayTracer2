
#include "../include/Ray_main.h"

#ifdef RAY_PRIMITIVES_H_
RAY_BEGIN

Ray::Ray()
{
	memset(this, 0, sizeof(Ray));
}
Ray::Ray(vec3& origin, vec3& direction)
{
	memset(this, 0, sizeof(Ray));
	this->origin = origin;
	this->direction = direction;
	this->length = FLT_MAX;
}
Ray::Ray(vec3& origin, vec3& direction, float length)
{
	memset(this, 0, sizeof(Ray));
	this->origin = origin;
	this->direction = direction;
	this->length = length;
}
Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz)
{
	memset(this, 0, sizeof(Ray));
	this->origin = vec3(ox, oy, oz);
	this->direction = vec3(dx, dy, dz);
	this->length = FLT_MAX;
}
Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz, float length)
{
	memset(this, 0, sizeof(Ray));
	this->origin = vec3(ox, oy, oz);
	this->direction = vec3(dx, dy, dz);
	this->length = length;
}
Ray::~Ray()
{
	memset(this, 0, sizeof(Ray));
}

RayHit::RayHit()
{
	memset(this, 0, sizeof(RayHit));
	this->traveled = FLT_MAX;
}
RayHit::~RayHit()
{
	memset(this, 0, sizeof(RayHit));
}

RayPath::RayPath()
{
	this->depth = 0;
}
RayPath::RayPath(int depth)
{
	this->depth = depth;
	this->path.resize(this->depth);
}
RayPath::~RayPath()
{
	this->path.clear();
}

void RayPath::operator+(const RayHit& hit)
{
	this->add(hit);
}
void RayPath::operator+=(const RayHit& hit)
{
	this->add(hit);
}
RayHit& RayPath::operator[](const int index)
{
	return this->get(index);
}

void RayPath::add(const RayHit& hit)
{
	if (this->depth <= this->path.length()) return;
	RayHit* last = &this->path.get(this->path.length() - 1);
	last->next = (RayHit*)&hit;
	this->path.add(hit);
}
RayHit& RayPath::get(const int index)
{
	return this->path.get(index);
}

SurfaceLumination::SurfaceLumination()
{
	memset(this, 0, sizeof(SurfaceLumination));
	this->color = COLOR(1.0f);
	this->diffuse = 1.0f;
	this->specular = 0.0f;
	this->brdf = 0.0f;
	this->attenuation = 1.0f;
}
SurfaceLumination::~SurfaceLumination()
{
	memset(this, 0, sizeof(SurfaceLumination));
}

RAY_END
#endif