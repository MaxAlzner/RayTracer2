
#include "../include/Ray_main.h"

#ifdef RAY_SHAPE_H_
RAY_BEGIN
	
Shape::Shape()
{
}
Shape::~Shape()
{
}

void Shape::build()
{
	Entity::build();

	this->material = new Material;
	this->material->build();
}
void Shape::unpack()
{
	this->material->unpack();
	delete this->material;

	Entity::unpack();
}

RAY_END
#endif