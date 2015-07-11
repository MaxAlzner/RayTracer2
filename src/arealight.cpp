
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{
			using namespace DataObjects;
			using namespace Tracer;
			using namespace Materials;

			inline RAY_API Lumination AreaLight::luminance(const Fragment& fragment)
			{
				if (fragment.material == 0)
				{
					return Lumination(Color(1.0f, 0.0f, 1.0f), Color(0.0f));
				}

				return Lumination(Color(0.0f), Color(0.0f));
			}

			inline RAY_API float AreaLight::occlusion(const Fragment& fragment)
			{
				if (fragment.material != 0)
				{

				}

				return 0.0f;
			}

		}
	}
}