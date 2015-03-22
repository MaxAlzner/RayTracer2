
#include "../include/Ray_main.h"

#ifdef RAY_ENTITY_H_
RAY_BEGIN

Entity::Entity()
{
}
Entity::~Entity()
{
}

void Entity::build()
{
	this->transform = new Transform;
	this->transform->build();
}
void Entity::unpack()
{
	this->transform->unpack();
	delete this->transform;
}

RAY_END
#endif