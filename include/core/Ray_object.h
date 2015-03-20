#ifndef RAY_OBJECT_H_
#define RAY_OBJECT_H_
RAY_BEGIN

class Object
{
public:

	virtual void build() = 0;
	virtual void unpack() = 0;

};

RAY_END
#endif