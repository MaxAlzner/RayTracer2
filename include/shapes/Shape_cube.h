#ifndef SHAPE_CUBE_H_
#define SHAPE_CUBE_H_
RAY_BEGIN
SHAPE_BEGIN

class Cube : public Shape
{
public:

	Cube();
	Cube(float width);
	~Cube();

	void build();
	void unpack();

	bool hitByRay(Ray& ray, RayHit& hit);

	float width;

};

SHAPE_END
RAY_END
#endif