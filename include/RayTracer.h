#pragma once

#include <MediaLoader.h>

#include <gmath.hpp>
#include <delegate.hpp>
#include <array.hpp>
#include <list.hpp>
#include <map.hpp>

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
	using namespace gmath;
	using namespace medialoader;
	using namespace medialoader::Image;
	using namespace medialoader::Mesh;

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
			class RAY_API GlassMaterial;
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

//using namespace cb;
//using namespace cb::Object;

#include "dataobjects\rayhit.h"
#include "dataobjects\lumination.h"
#include "dataobjects\lighting.h"
#include "dataobjects\fragment.h"

#include "shapes\traceshape.h"
#include "shapes\sphere.h"
#include "shapes\axiscube.h"
#include "shapes\octpartitionshape.h"

#include "components\component.h"
#include "components\transform.h"
#include "components\meshfilter.h"
#include "components\texturefilter.h"

#include "components\materials\material.h"
#include "components\materials\diffusematerial.h"
#include "components\materials\blinnmaterial.h"
#include "components\materials\phongmaterial.h"
#include "components\materials\cooktorrancematerial.h"
#include "components\materials\glassmaterial.h"

#include "components\cameras\camera.h"

#include "components\lights\light.h"
#include "components\lights\pointlight.h"
#include "components\lights\directionallight.h"
#include "components\lights\spotlight.h"
#include "components\lights\arealight.h"

#include "tracer\object.h"
#include "tracer\entity.h"
#include "tracer\tracestack.h"
#include "tracer\tracepath.h"
#include "tracer\photo.h"
#include "tracer\photoemitter.h"