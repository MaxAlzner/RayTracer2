
#include "../include/Ray_main.h"

#ifdef RAY_LIGHT_H_
RAY_BEGIN

Light::Light()
{
}
Light::~Light()
{
}

void Light::build()
{
	Entity::build();

	this->color = COLOR(1.0f);
	this->falloff = vec3(0.2f, 1.6f, 4.0f);
	this->shadowIntensity = 0.25f;
}
void Light::unpack()
{
	Entity::unpack();
}

void Light::lumination(RayHit& hit, ARRAY<Shape*>& stack)
{
	vec3 light = this->transform->position - hit.intersection;
	float dist = float(light.length());
	light = normalize(light);

	Ray toLight(hit.intersection, light, dist);
	RayHit shadowCheck;
	bool occluded = false;
	for (int i = 0; i < stack.length(); i++)
	{
		Shape* shape = stack[i];
		occluded = occluded || shape->hitByRay(toLight, shadowCheck);
	}
	
	vec3 half = normalize(hit.normal + hit.ray.direction);
	float atten = 1.0f / (this->falloff.x + (this->falloff.y * dist) + (this->falloff.z * dist * dist));
	if (occluded) atten = 0.0f;

	float n_dot_l = dot(light, hit.normal);
	float n_dot_h = dot(hit.normal, half);
	float n_dot_v = dot(hit.normal, hit.ray.direction);
	float h_dot_v = dot(half, hit.ray.direction);
	float h_dot_l = dot(half, light);
	float diffuse = clamp(n_dot_l, 0.1f, 1.0f);
	float specular = hit.surface->material->specularIntensity;

	float g1 = (2.0f * n_dot_h * n_dot_v) / h_dot_v;
	float g2 = (2.0f * n_dot_h * n_dot_l) / h_dot_v;
	float g = 1.0f;
	if (g1 < g) g = g1;
	if (g2 < g) g = g2;
	float m = hit.surface->material->roughness * hit.surface->material->roughness;
	float r = (1.0f / (m * pow(n_dot_h, 4.0f))) * exp((pow(n_dot_h, 2.0f) - 1.0f) / (m * pow(n_dot_h, 2.0f)));
	float f = (hit.surface->material->refractionIndex + pow(1.0f - h_dot_v, 5.0f)) * (1.0f - hit.surface->material->refractionIndex);
	float brdf = max((abs(f * r * g) / n_dot_v), 0.0f);

	SurfaceLumination* lum = new SurfaceLumination;
	lum->color = this->color;
	lum->diffuse = diffuse;
	lum->specular = specular;
	lum->brdf = brdf;
	lum->attenuation = atten;
	hit.lumination = lum;
}

RAY_END
#endif