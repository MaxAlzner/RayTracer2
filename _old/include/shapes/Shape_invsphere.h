#ifndef SHAPE_INVSPHERE_H_
#define SHAPE_INVSPHERE_H_
RAY_BEGIN
SHAPE_BEGIN

class InvSphere : public Shape
{
public:

	InvSphere();
	InvSphere(float radius);
	~InvSphere();

	void build();
	void unpack();

	bool hitByRay(Ray& ray, RayHit& hit);

	float radius;

};

SHAPE_END
RAY_END
#endif