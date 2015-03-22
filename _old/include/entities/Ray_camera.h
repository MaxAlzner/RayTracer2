#ifndef RAY_CAMERA_H_
#define RAY_CAMERA_H_
RAY_BEGIN

class Camera : public Entity
{
public:

	Camera();
	~Camera();

	virtual void build();
	virtual void unpack();

	void adjust();

	RayPath* traceRay(float u, float v, ARRAY<Shape*>& stack);

	Ray getRay(float u, float v);
	Ray getRay(vec2& uv);

	vec2 aperture;
	float focalDepth;
	int reflectDepth;
	int multisampleDepth;

private:

	struct
	{
		vec3 p1;
		vec3 p2;
		vec3 p3;
		vec3 p4;
		vec3 px;
		vec3 py;
		vec3 focal;
	} viewport;

};

RAY_END
#endif