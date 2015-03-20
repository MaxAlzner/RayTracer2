#ifndef RAY_LIGHT_H_
#define RAY_LIGHT_H_
RAY_BEGIN

class Light : public Entity
{
public:

	Light();
	~Light();

	virtual void build();
	virtual void unpack();

	void lumination(RayHit& hit, ARRAY<Shape*>& stack);

	COLOR color;
	vec3 falloff;
	float shadowIntensity;

};

RAY_END
#endif