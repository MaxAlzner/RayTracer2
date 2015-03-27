
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include "..\include\RayTracer.h"

using namespace cb::Object;
using namespace cb::Object::Image;
using namespace cb::Object::Mesh;

using namespace Ray;
using namespace Ray::Components;
using namespace Ray::Tracer;

int main(int argc, char** argv)
{
	Shape* sphere1 = new Shapes::Sphere(2.1f);
	sphere1->build();
	Shape* sphere2 = new Shapes::Sphere(2.0f);
	sphere2->build();
	Shape* cube1 = new Shapes::AxisCube;
	cube1->build();

	Photo* photo = new Photo(240, 160);
	photo->build();
	TraceStack* stack = new TraceStack;
	stack->build();

	Entity* entity0 = new Entity;
	entity0->build();
	entity0->add(new Camera);
	//entity0->transform->position.y -= 4.8f;
	//entity0->transform->position.z -= 4.8f;
	//entity0->transform->rotation.x += 30.0f;
	stack->add(entity0);

	Entity* entity1 = new Entity;
	entity1->build();
	entity1->attach(sphere1);
	entity1->transform->position.x -= 3.2f;
	entity1->transform->position.y -= 2.0f;
	stack->add(entity1);

	Entity* entity2 = new Entity;
	entity2->build();
	entity2->attach(sphere2);
	entity2->transform->position.x += 3.2f;
	entity2->transform->position.y -= 3.0f;
	stack->add(entity2);

	Entity* entity3 = new Entity;
	entity3->build();
	entity3->attach(cube1);
	entity3->transform->position.x += 0.0f;
	entity3->transform->position.y += 1.2f;
	entity3->transform->position.z -= 0.8f;
	entity3->transform->scale *= 2.0f;
	stack->add(entity3);

	stack->camera->focalDepth = 3.4f;

#if 1
	const int frames = 8;
	for (int i = 0; i < frames; i++)
	{
		float k = float(i) / float(frames);
		float theta = k * Math::pi() * 2.0f;
		float u = cos(theta);
		float v = sin(theta);

		entity0->transform->position.x = 6.4f * u;
		entity0->transform->position.z = 6.4f * v;
		entity0->transform->rotation.y = (k * 360.0f) + 90.0f;

		char* filename = new char[32];
		memset(filename, 0, sizeof(char) * 32);
		sprintf(filename, "trace.00%d.png", i + 1);

		photo->emit(stack);
		Surface* surface = photo->flatten();
		Surface::WritePng(surface, String(filename));

		surface->dispose();
		delete surface;
		delete[] filename;
	}
#else
	photo->emit(stack);
	Surface* surface = photo->flatten();
	Surface::WritePng(surface, "trace.001.png");
	surface->dispose();
	delete surface;
#endif

	stack->dispose();
	delete stack;
	photo->dispose();
	delete photo;

	cube1->dispose();
	delete cube1;
	sphere2->dispose();
	delete sphere2;
	sphere1->dispose();
	delete sphere1;

	//_getch();
	return 0;
}