
#define _CRT_SECURE_NO_WARNINGS

#include <RayTracer.h>
#include <conio.h>
#include <dirent.h>

using namespace Ray;
using namespace Ray::Shapes;
using namespace Ray::Components;
using namespace Ray::Tracer;

static struct
{
	int width;
	int height;
	int multiSample;
	int reflectDepth;
} Config;

static Array<TraceShape*> shapes(32);
static Array<Surface*> textures(32);

static Photo* photo = 0;
static TraceStack* stack = 0;

static void ParseAddTextureNode(XmlNode* node, Entity* entity)
{
	String type = XmlFile::Value(node->last_attribute("type"));
	String src = XmlFile::Value(node->last_attribute("src"));
	Surface* surface = new Surface;
	textures.add(surface);
	surface->read(src);

	if (type == "diffuse")
	{
		entity->attach(surface, TextureFilter::TEXTURE_COLOR);
	}
	else if (type == "normal")
	{
		entity->attach(surface, TextureFilter::TEXTURE_NORMAL);
	}
	else if (type == "specular")
	{
		entity->attach(surface, TextureFilter::TEXTURE_SPECULAR);
	}
	else if (type == "transparency")
	{
		entity->attach(surface, TextureFilter::TEXTURE_TRANSPARENCY);
	}
	else if (type == "reflect")
	{
		entity->attach(surface, TextureFilter::TEXTURE_REFLECT);
	}
	else if (type == "emissive")
	{
		entity->attach(surface, TextureFilter::TEXTURE_EMISSIVE);
	}
	else if (type == "displacement")
	{
		entity->attach(surface, TextureFilter::TEXTURE_DISPLACEMENT);
	}
}

static void ParseTransformNode(XmlNode* node, Entity* entity)
{
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		float v = XmlFile::ParseFloat(node, 0.0f);
		float x = XmlFile::ParseFloat(node->last_attribute("x"), 0.0f);
		float y = XmlFile::ParseFloat(node->last_attribute("y"), 0.0f);
		float z = XmlFile::ParseFloat(node->last_attribute("z"), 0.0f);
		if (name == "translate")
		{
			entity->transform->position += vec3(x, y, z) + v;
		}
		else if (name == "rotate")
		{
			entity->transform->rotation += vec3(x, y, z) + v;
		}
		else if (name == "scale")
		{
			v = v == 0.0f ? 1.0f : v;
			x = x == 0.0f ? 1.0f : x;
			y = y == 0.0f ? 1.0f : y;
			z = z == 0.0f ? 1.0f : z;
			entity->transform->scale *= vec3(x, y, z) * v;
		}

		node = node->next_sibling();
	}
}

static void ParseMaterialNode(XmlNode* node, Entity* entity)
{
	String type = XmlFile::Value(node->last_attribute("type"));
	Component* material =
		type == "Diffuse" ? new Materials::DiffuseMaterial :
		type == "Blinn" ? new Materials::BlinnMaterial(XmlFile::ParseFloat(node->last_attribute("exponent"), 32.0f)) :
		type == "Phong" ? new Materials::PhongMaterial(XmlFile::ParseFloat(node->last_attribute("exponent"), 16.0f)) :
		type == "CookTorrance" ? new Materials::CookTorranceMaterial(XmlFile::ParseFloat(node->last_attribute("roughness"), 1.0f), XmlFile::ParseFloat(node->last_attribute("refractionIndex"), 1.3f)) :
		type == "Glass" ? new Materials::GlassMaterial :
		(Component*)0;
	entity->add(material);
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		if (name == "add")
		{
			ParseAddTextureNode(node, entity);
		}

		node = node->next_sibling();
	}
}

static void ParseShapeNode(XmlNode* node, Entity* entity)
{
	String type = XmlFile::Value(node->last_attribute("type"));
	TraceShape* shape =
		type == "Sphere" ? new Sphere :
		type == "AxisCube" ? new AxisCube :
		type == "OctPartitionShape" ? new OctPartitionShape :
		(TraceShape*)0;
	shapes.add(shape);
	entity->attach(shape);
}

static void ParseComponentsNode(XmlNode* node, Entity* entity)
{
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		String type = XmlFile::Value(node->last_attribute("type"));
		if (name == "add")
		{
			Component* component =
				type == "Camera" ? new Cameras::Camera(
				vec2(XmlFile::ParseFloat(node->last_attribute("apertureX"), 4.0f), XmlFile::ParseFloat(node->last_attribute("apertureY"), 3.0f)),
				XmlFile::ParseFloat(node->last_attribute("focalDepth"), -1.0f)) :
				type == "DirectionalLight" ? new Lights::PointLight(XmlFile::ParseFloat(node->last_attribute("intensity"), 1.0f)) :
				type == "PointLight" ? new Lights::DirectionalLight(XmlFile::ParseFloat(node->last_attribute("intensity"), 1.0f)) :
				type == "SpotLight" ? new Lights::SpotLight(
				XmlFile::ParseFloat(node->last_attribute("angle"), 60.0f),
				XmlFile::ParseFloat(node->last_attribute("intensity"), 1.0f)) :
				type == "AreaLight" ? new Lights::AreaLight(
				vec2(XmlFile::ParseFloat(node->last_attribute("areaX"), 1.0f), XmlFile::ParseFloat(node->last_attribute("areaY"), 1.0f)),
				XmlFile::ParseFloat(node->last_attribute("intensity"), 1.0f)) :
				(Component*)0;
			entity->add(component);
		}

		node = node->next_sibling();
	}
}

static void ParseEntityNode(XmlNode* node)
{
	Entity* entity = new Entity;
	entity->build();
	stack->add(entity);
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		if (name == "transform")
		{
			ParseTransformNode(node, entity);
		}
		else if (name == "material")
		{
			ParseMaterialNode(node, entity);
		}
		else if (name == "shape")
		{
			ParseShapeNode(node, entity);
		}
		else if (name == "components")
		{
			ParseComponentsNode(node, entity);
		}

		node = node->next_sibling();
	}
}

static void ParsePhotoNode(XmlNode* node)
{
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		if (name == "width")
		{
			Config.width = XmlFile::ParseInt(node, 400);
		}
		else if (name == "height")
		{
			Config.height = XmlFile::ParseInt(node, 300);
		}
		else if (name == "multiSample")
		{
			Config.multiSample = XmlFile::ParseInt(node, 0);
		}
		else if (name == "reflectDepth")
		{
			Config.reflectDepth = XmlFile::ParseInt(node, 0);
		}

		node = node->next_sibling();
	}
}

static void ParseStackNode(XmlNode* node)
{
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		if (name == "entity")
		{
			ParseEntityNode(node);
		}

		node = node->next_sibling();
	}
}

static void ParseTraceNode(XmlNode* node)
{
	node = node->first_node();
	while (node != 0)
	{
		String name = node->name();
		if (name == "photo")
		{
			ParsePhotoNode(node);
		}
		else if (name == "stack")
		{
			ParseStackNode(node);
		}

		node = node->next_sibling();
	}
}

int main(int argc, char** argv)
{
	if (argc < 1 || argv == 0)
	{
		return ERROR;
	}

	Config.width = 400;
	Config.height = 300;
	Config.reflectDepth = 1;
	Config.multiSample = 1;

	stack = new TraceStack;
	stack->build();

	XmlFile* file = new XmlFile;
	String filepath = argv[0];
	filepath.trimEnd('\\');

	DIR* directory = opendir((char*)filepath);
	dirent* ent = readdir(directory);
	while (ent != 0)
	{
		String filename = ent->d_name;
		if (filename.endsWith("trace"))
		{
			file->read(filepath + filename);
			break;
		}

		ent = readdir(directory);
	}

	if (file->root != 0)
	{
		ParseTraceNode(file->root);
	}

	file->release();
	delete file;
	closedir(directory);

	photo = new Photo(Config.width, Config.height, Config.reflectDepth, Config.multiSample);
	photo->build();

	const int frames = 1;
	for (int i = 0; i < frames; i++)
	{
		float k = float(i) / (float(frames) * 1.0f);
		float theta = (k * PI * 2.0f);
		float u = cos(theta);
		float v = sin(theta);

		if (stack->camera != 0)
		{
			stack->camera->object->transform->position.x = 12.8f * u;
			stack->camera->object->transform->position.y = 4.4f;
			stack->camera->object->transform->position.z = 12.8f * v;
			stack->camera->object->transform->rotation.x = -2.0f;
			stack->camera->object->transform->rotation.y = (k * 360.0f) + 90.0f;
			stack->camera->object->transform->rotation.z = 0.0f;
		}

		char* filename = new char[32];
		memset(filename, 0, sizeof(char) * 32);
		sprintf(filename, "trace.%03d.png", i + 1);

		photo->render(stack);
		Surface* surface = photo->flatten();
		surface->write(String(filename));
		printf("%s\n", filename);

		surface->release();
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
			surface->release();
			delete surface;
		}
	}

	for (int i = 0; shapes.inside(i); i++)
	{
		Shape* shape = shapes[i];
		if (shape != 0)
		{
			shape->release();
			delete shape;
		}
	}

	textures.clear();
	shapes.clear();

	//_getch();
	return 0;
}