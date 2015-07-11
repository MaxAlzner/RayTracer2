
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

			inline RAY_API Lumination DirectionalLight::luminance(const Fragment& fragment)
			{
				if (fragment.material == 0)
				{
					return Lumination(Color(1.0f, 0.0f, 1.0f), Color(0.0f));
				}

				vec3 l = this->object->transform->forward * -1.0f;
				float atten = this->intensity / float(this->object->stack->lights.count());

				Lighting data(l, this->occlusion(fragment) * atten);

				return fragment.material->shade(data, fragment);
			}

			inline RAY_API float DirectionalLight::occlusion(const Fragment& fragment)
			{
				if (fragment.material != 0)
				{
					ray to(fragment.position, this->object->transform->forward * -1.0f);
					Fragment occluded = this->object->stack->trace(to, 0);
					return occluded.material != 0 && occluded.material != fragment.material ? 0.0f : 1.0f;
				}

				return 0.0f;
			}

		}
	}
}