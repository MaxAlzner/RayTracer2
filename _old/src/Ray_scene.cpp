
#include "../include/Ray_main.h"

#ifdef RAY_SCENE_H_
RAY_BEGIN

Scene::Scene()
{
	this->renderable.resize(10);
	this->lights.resize(10);
}
Scene::~Scene()
{
}

void Scene::build()
{
	this->mainCamera = new Camera;
	this->mainCamera->build();
	for (int i = 0; i < this->renderable.length(); i++)
	{
		Shape* s = this->renderable[i];
		if (!s) continue;
		s->build();
	}
	for (int i = 0; i < this->lights.length(); i++)
	{
		Light* l = this->lights[i];
		if (!l) continue;
		l->build();
	}
}
void Scene::unpack()
{
	for (int i = 0; i < this->lights.length(); i++)
	{
		Light* l = this->lights[i];
		if (!l) continue;
		l->unpack();
		delete l;
	}
	this->lights.clear();
	for (int i = 0; i < this->renderable.length(); i++)
	{
		Shape* s = this->renderable[i];
		if (!s) continue;
		s->unpack();
		delete s;
	}
	this->renderable.clear();
	this->mainCamera->unpack();
	delete this->mainCamera;
}

void Scene::prepare()
{
	this->mainCamera->transform->recalculate();
	this->mainCamera->adjust();
	for (int i = 0; i < this->renderable.length(); i++)
	{
		Shape* s = this->renderable[i];
		if (!s) continue;
		s->transform->recalculate();
	}
	for (int i = 0; i < this->lights.length(); i++)
	{
		Light* l = this->lights[i];
		if (!l) continue;
		l->transform->recalculate();
	}
}
void Scene::illuminate(RayPath* path)
{
	for (int i = 0; i < path->path.length(); i++)
	{
		RayHit* hit = &path->path[i];
		for (int k = 0; k < this->lights.length(); k++)
		{
			Light* light = this->lights[k];

			light->lumination(*hit, this->renderable);
		}
	}
}
Photo* Scene::render()
{
	int width = 240;
	int height = 160;
	Photo* photo = new Photo(width, height);

	for (int i = 0; i < height; i++)
	{
		for (int k = 0; k < width; k++)
		{
			float u = float(k) / float(width);
			float v = float(i) / float(height);

			RayPath* path = this->mainCamera->traceRay(u, v, this->renderable);
			if (path == 0) continue;

			this->illuminate(path);
			photo->registerRay(k, i, *path);
			delete path;
		}
	}

	return photo;
}

RAY_END
#endif