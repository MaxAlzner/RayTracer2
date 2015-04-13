
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include "..\include\RayTracer.h"

using namespace cb::Object;
using namespace cb::Object::Image;
using namespace cb::Object::Mesh;

using namespace Ray;
using namespace Ray::Shapes;
using namespace Ray::Components;
using namespace Ray::Tracer;

static Collection::Array<TraceShape*> shapes(32);
static Collection::Array<Surface*> textures(32);

static Photo* photo = 0;
static TraceStack* stack = 0;

Entity* Build(vec3 position, vec3 rotation, vec3 scale, Materials::Material* material, Surface* color, Surface* normal, Surface* specular)
{
	Entity* entity = new Entity;
	entity->build();
	entity->transform->position = position;
	entity->transform->rotation = rotation;
	entity->transform->scale = scale;
	if (material != 0)
	{
		entity->add(material);
	}

	if (color != 0)
	{
		entity->attach(color, TextureFilter::TEXTURE_COLOR);
	}

	if (normal != 0)
	{
		entity->attach(normal, TextureFilter::TEXTURE_NORMAL);
	}

	if (specular != 0)
	{
		entity->attach(specular, TextureFilter::TEXTURE_SPECULAR);
	}

	stack->add(entity);
	return entity;
}

Entity* Camera(vec3 position, vec3 rotation, vec2 aperture, float focalDepth)
{
	Entity* entity = Build(position, rotation, vec3(1.0f), 0, 0, 0, 0);
	Cameras::Camera* camera = new Cameras::Camera();
	entity->add(camera);
	camera->adjust(aperture.x, aperture.y);
	camera->focalDepth = focalDepth;
	return entity;
}

Entity* StaticCube(vec3 position, float scale, Materials::Material* material, Surface* color, Surface* normal, Surface* specular)
{
	Entity* entity = Build(position, vec3(0.0f), vec3(scale), material, color, normal, specular);
	TraceShape* cube = new Shapes::AxisCube;
	cube->build();
	shapes.add(cube);
	entity->attach(cube);
	return entity;
}

Entity* StaticSphere(vec3 position, float radius, Materials::Material* material, Surface* color, Surface* normal, Surface* specular)
{
	Entity* entity = Build(position, vec3(0.0f), vec3(1.0f), material, color, normal, specular);
	TraceShape* sphere = new Shapes::Sphere(radius);
	sphere->build();
	shapes.add(sphere);
	entity->attach(sphere);
	return entity;
}

Entity* StaticMesh(vec3 position, vec3 rotation, vec3 scale, TraceShape* shape, Materials::Material* material, Surface* color, Surface* normal, Surface* specular)
{
	Entity* entity = Build(position, rotation, scale, material, color, normal, specular);
	entity->attach(shape);
	return entity;
}

Entity* PointLight(vec3 position, float intensity)
{
	Entity* entity = Build(position, vec3(0.0f), vec3(1.0f), 0, 0, 0, 0);
	entity->add(new Lights::PointLight(intensity));
	return entity;
}

Entity* DirectionalLight(vec3 rotation, float intensity)
{
	Entity* entity = Build(vec3(0.0f), rotation, vec3(1.0f), 0, 0, 0, 0);
	entity->add(new Lights::DirectionalLight(intensity));
	return entity;
}

int main(int argc, char** argv)
{
	for (int i = 0; i < 8; i++)
	{
		OctPartitionShape* shape = new OctPartitionShape;
		shape->build();
		shapes.add(shape);
	}

	Shape::ReadWavefront(shapes[0], "data\\puzzle.obj");

	for (int i = 0; i < textures.capacity(); i++)
	{
		Surface* surface = new Surface;
		surface->build();
		textures.add(surface);
	}

	Surface::ReadBitmap(textures[0], "data\\dungeon_arch_door_dif.bmp");
	Surface::ReadBitmap(textures[1], "data\\dungeon_arch_door_normal.bmp");
	Surface::ReadBitmap(textures[2], "data\\dungeon_arch_door_spec.bmp");
	Surface::ReadBitmap(textures[3], "data\\dungeon_floor_dif.bmp");
	Surface::ReadBitmap(textures[4], "data\\dungeon_floor_normal.bmp");
	Surface::ReadBitmap(textures[5], "data\\dungeon_floor_spec.bmp");
	Surface::ReadBitmap(textures[6], "data\\dungeon_wall_dirt_dif.bmp");
	Surface::ReadBitmap(textures[7], "data\\dungeon_wall_dirt_normal.bmp");
	Surface::ReadBitmap(textures[8], "data\\dungeon_wall_dirt_spec.bmp");

	photo = new Photo(800, 600);
	photo->build();
	stack = new TraceStack;
	stack->build();

	Entity* camera = Camera(vec3(0.0f, 2.4f, 0.0f), vec3(-20.0f, 0.0f, 0.0f), vec2(4.0f, 3.0f), 3.4f);

	StaticCube(
		vec3(0.0f, 1.2f, -3.2f), 2.0f,
		//new Materials::PhongMaterial,
		new Materials::CookTorranceMaterial(0.1f, 1.5f),
		textures[3],
		textures[4],
		textures[5]
		);
	StaticCube(
		vec3(-4.0f, 0.1f, -1.8f), 1.4f,
		new Materials::PhongMaterial,
		//new Materials::DiffuseMaterial,
		textures[3],
		textures[4],
		textures[5]
		);
	StaticSphere(
		vec3(-3.2f, -2.0f, 0.0f), 2.1f,
		new Materials::PhongMaterial(24.0f),
		//new Materials::CookTorranceMaterial(0.1f, 1.1f),
		textures[6],
		textures[7],
		textures[8]
		);
	StaticSphere(
		vec3(-1.0f, 0.5f, 0.0f), 0.4f,
		new Materials::BlinnMaterial,
		//new Materials::DiffuseMaterial,
		textures[0],
		textures[1],
		textures[2]
		);

#if 0
	StaticMesh(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(5.0f),
		shapes[0],
		new Materials::CookTorranceMaterial(0.8f, 1.1f),
		textures[3],
		textures[4],
		textures[5]
		);
#endif

	DirectionalLight(vec3(-20.0f, 135.0f, 0.0f), 1.0f);
	PointLight(vec3(-6.4f, 0.2f, -0.8f), 1.0f);
	PointLight(vec3(-4.0f, 1.0f, -6.4f), 1.0f);
	PointLight(vec3(-2.0f, 0.2f, 0.0f), 8.0f);

	const int frames = 8;
	for (int i = 0; i < frames; i++)
	{
		float k = float(i) / float(frames * 2);
		float theta = k * Math::pi() * 2.0f;
		float u = cos(theta);
		float v = sin(theta);

		camera->transform->position.x = 8.0f * u;
		camera->transform->position.z = 8.0f * v;
		camera->transform->rotation.y = (k * 360.0f) + 90.0f;

		char* filename = new char[32];
		memset(filename, 0, sizeof(char) * 32);
		sprintf(filename, "trace.%03d.png", i + 1);

		photo->render(stack);
		Surface* surface = photo->flatten();
		Surface::WritePng(surface, String(filename));
		printf("%s\n", filename);

		surface->dispose();
		delete surface;
		delete[] filename;
	}

	stack->dispose();
	delete stack;
	photo->dispose();
	delete photo;

	for (int i = 0; textures.inside(i); i++)
	{
		Surface* surface = textures[i];
		if (surface != 0)
		{
			surface->dispose();
			delete surface;
		}
	}

	for (int i = 0; shapes.inside(i); i++)
	{
		Shape* shape = shapes[i];
		if (shape != 0)
		{
			shape->dispose();
			delete shape;
		}
	}

	textures.clear();
	shapes.clear();

	//_getch();
	return 0;
}