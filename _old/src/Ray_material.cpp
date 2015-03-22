
#include "../include/Ray_main.h"

#ifdef RAY_MATERIAL_H_
RAY_BEGIN

Material::Material()
{
}
Material::~Material()
{
}

void Material::build()
{
	this->overlay = COLOR(1.0f);
	this->highlight = COLOR(1.0f);
	this->roughness = 0.6f;
	this->refractionIndex = 1.3333f;
	this->specularIntensity = 1.0f;
}
void Material::unpack()
{
}

RAY_END
#endif