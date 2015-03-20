#ifndef SHAPE_SPHERE_H_
#define SHAPE_SPHERE_H_
RAY_BEGIN
SHAPE_BEGIN

class Sphere : public Shape
{
public:

	Sphere();
	Sphere(float radius);
	~Sphere();

	void build();
	void unpack();

	bool hitByRay(Ray& ray, RayHit& hit);

	float radius;

};

SHAPE_END
RAY_END
#endif