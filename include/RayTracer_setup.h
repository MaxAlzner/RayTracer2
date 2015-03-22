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
	namespace Primitives
	{
		class RAY_API RayHit;
		class RAY_API HitBuffer;
	}

	namespace Components
	{
		class RAY_API Component;
		class RAY_API Transform;
		class RAY_API Material;
		class RAY_API MeshFilter;
		class RAY_API Camera;
	}

	namespace Tracer
	{
		class RAY_API Entity;
		class RAY_API TraceStack;
		class RAY_API Photo;
	}
}

#endif