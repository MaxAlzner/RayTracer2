
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Lights
		{
			using namespace Collection;
			using namespace DataObjects;
			using namespace Tracer;
			using namespace Materials;

			inline RAY_API Lumination DirectionalLight::luminance(const Fragment& fragment)
			{
				if (fragment.material == 0)
				{
					return Lumination(Color(1.0f, 0.0f, 1.0f), Color(0.0f));
				}

				vec3 l = this->object->transform->forward * -1.0f;
				float atten = this->intensity / float(this->object->stack->lights.count());

				Lighting data(l, this->occluded(fragment) ? 0.1f : atten);

				return fragment.material->shade(data, fragment);
			}

			inline RAY_API bool DirectionalLight::occluded(const Fragment& fragment)
			{
				if (fragment.material != 0)
				{
					ray to(fragment.position, this->object->transform->forward * -1.0f);
					Entity* occluder = this->object->stack->trace(to, 0);
					return occluder != 0 && occluder != fragment.material->object;
				}

				return false;
			}

		}
	}
}