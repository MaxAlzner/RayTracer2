
#include "..\include\RayTracer.h"

using namespace Ray;
using namespace Ray::Components;
using namespace Ray::Tracer;

int main(int argc, char** argv)
{
	Photo* photo = new Photo(240, 160);
	photo->build();
	TraceStack* stack = new TraceStack;
	stack->build();

	Entity* camera = new Entity;
	camera->build();
	camera->transform->position.z -= 4.0f;
	camera->add(new Camera);
	stack->add(camera);
	stack->camera = (Camera*)camera->findComponent("Camera");

	stack->dispose();
	delete stack;
	photo->dispose();
	delete photo;
	return 0;
}