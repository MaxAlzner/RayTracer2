#ifndef RAYTRACER_SETUP
#define RAYTRACER_SETUP

#if defined(_WIN32)
#if defined(RAY_EXPORT)
#define RAY_API __declspec(dllexport)
#else
#define RAY_API __declspec(dllimport)
#endif
#define RAY_TEMPLATE_API __declspec(dllexport)
#else
#define RAY_API
#define RAY_TEMPLATE_API
#endif

#define RAY_NAMESPACE Ray

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{
		class RAY_API RayHit;
		class RAY_API Lumination;
		class RAY_API Lighting;
		class RAY_API Fragment;
	}

	namespace Shapes
	{
		class RAY_API TraceShape;
		class RAY_API Sphere;
		class RAY_API AxisCube;
		class RAY_API OctPartitionShape;
	}

	namespace Components
	{
		class RAY_API Component;
		class RAY_API Transform;
		class RAY_API MeshFilter;
		class RAY_API TextureFilter;

		namespace Materials
		{
			class RAY_API Material;
			class RAY_API DiffuseMaterial;
			class RAY_API BlinnMaterial;
			class RAY_API PhongMaterial;
			class RAY_API CookTorranceMaterial;
		}

		namespace Cameras
		{
			class RAY_API Camera;
		}

		namespace Lights
		{
			class RAY_API Light;
			class RAY_API PointLight;
			class RAY_API DirectionalLight;
			class RAY_API SpotLight;
			class RAY_API AreaLight;
		}
	}

	namespace Tracer
	{
		class RAY_API Entity;
		class RAY_API TraceStack;
		class RAY_API TracePath;
		class RAY_API Photo;
		class RAY_API PhotoEmitter;
	}
}

#endif