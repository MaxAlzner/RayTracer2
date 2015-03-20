#ifndef RAY_TRANSFORM_H_
#define RAY_TRANSFORM_H_
RAY_BEGIN

class Transform : public Object
{
public:

	Transform();
	~Transform();

	void build();
	void unpack();

	void setTranslationX(float v);
	void setTranslationY(float v);
	void setTranslationZ(float v);
	void setRotationX(float v);
	void setRotationY(float v);
	void setRotationZ(float v);
	void setScaleX(float v);
	void setScaleY(float v);
	void setScaleZ(float v);
	void setTranslation(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void zero();

	void lookAt(float x, float y, float z);

	void recalculate();

	vec3 right;
	vec3 up;
	vec3 forward;
	vec3 position;

	mat4 space;
	mat3 spaceNormal;
	mat4 transformation;

private:

	vec3 translation;
	vec3 rotation;
	vec3 scaled;

};

RAY_END
#endif