#ifndef RAY_MATERIAL_H_
#define RAY_MATERIAL_H_
RAY_BEGIN

class Material : public Object
{
public:

	Material();
	~Material();

	void build();
	void unpack();

	COLOR overlay;
	COLOR highlight;
	float roughness;
	float refractionIndex;
	float specularIntensity;

};

RAY_END
#endif