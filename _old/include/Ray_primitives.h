#ifndef RAY_PRIMITIVES_H_
#define RAY_PRIMITIVES_H_
RAY_BEGIN

typedef struct Ray Ray;
typedef struct RayHit RayHit;
typedef struct RayPath RayPath;
typedef struct SurfaceLumination SurfaceLumination;

typedef struct Ray
{
	Ray();
	Ray(vec3& origin, vec3& direction);
	Ray(vec3& origin, vec3& direction, float length);
	Ray(float ox, float oy, float oz, float dx, float dy, float dz);
	Ray(float ox, float oy, float oz, float dx, float dy, float dz, float length);
	~Ray();

	vec3 origin;
	vec3 direction;
	float length;

} Ray;

/*
  Ray ray : ray involved in hit
  vec3 intersection : position of intersection
  float traveled : distance traveled from ray origin to intersection
  vec3 normal : normal of where the ray hit on the surface
  vec2 texcoord : texcoord of where the ray hit on the surface
  Entity* surface : surface that was hit
  RayHit* next : next rayhit in the reflection chain
*/
typedef struct RayHit
{
	RayHit();
	~RayHit();

	Ray ray;
	vec3 intersection;
	float traveled;
	vec3 normal;
	vec2 texcoord;
	Shape* surface;
	SurfaceLumination* lumination;
	RayHit* next;

} RayHit;

typedef struct RayPath
{
	RayPath();
	RayPath(int depth);
	~RayPath();

	void operator+(const RayHit& hit);
	void operator+=(const RayHit& hit);
	RayHit& operator[](const int index);

	void add(const RayHit& hit);
	RayHit& get(const int index);

	ARRAY<RayHit> path;
	int depth;

} RayPath;

typedef struct SurfaceLumination
{
	SurfaceLumination();
	~SurfaceLumination();

	COLOR color;
	float diffuse;
	float specular;
	float brdf;
	float attenuation;

} SurfaceLumination;

RAY_END
#endif