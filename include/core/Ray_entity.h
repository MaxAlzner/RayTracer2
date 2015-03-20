#ifndef RAY_ENTITY_H_
#define RAY_ENTITY_H_
RAY_BEGIN

class Entity : public Object
{
public:

	Entity();
	~Entity();

	virtual void build();
	virtual void unpack();

	Transform* transform;

};

RAY_END
#endif