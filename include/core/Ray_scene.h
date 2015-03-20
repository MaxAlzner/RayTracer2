#ifndef RAY_SCENE_H_
#define RAY_SCENE_H_
RAY_BEGIN

class Scene : public Object
{
public:

	Scene();
	~Scene();

	void build();
	void unpack();

	void prepare();
	void illuminate(RayPath* path);
	Photo* render();

	Camera* mainCamera;
	ARRAY<Shape*> renderable;
	ARRAY<Light*> lights;

};

RAY_END
#endif