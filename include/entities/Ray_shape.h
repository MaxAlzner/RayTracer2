#ifndef RAY_SHAPE_H_
#define RAY_SHAPE_H_
RAY_BEGIN

class Shape : public Entity
{
public:
	
	Shape();
	~Shape();

	virtual void build();
	virtual void unpack();

	virtual bool hitByRay(Ray& ray, RayHit& hit) = 0;
	
	Material* material;
};

RAY_END
#endif