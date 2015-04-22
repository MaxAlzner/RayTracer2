
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

			inline RAY_API Lumination PointLight::luminance(const Fragment& fragment)
			{
				if (fragment.material == 0)
				{
					return Lumination(Color(1.0f, 0.0f, 1.0f), Color(0.0f));
				}

				vec3 l = this->object->transform->position - fragment.position;
				float d = Math::magnitude(l);
				l = Math::normalize(l);

				float atten = Math::min(this->intensity / d, 1.0f);

				Lighting data(l, this->occlusion(fragment) * atten);

				return fragment.material->shade(data, fragment);
			}

			inline RAY_API float PointLight::occlusion(const Fragment& fragment)
			{
				if (fragment.material != 0)
				{
					vec3 toLight = this->object->transform->position - fragment.position;
					ray to(fragment.position, Math::normalize(toLight), Math::magnitude(toLight));
					Fragment occluded = this->object->stack->trace(to, 0);
					return occluded.material != 0 && occluded.material != fragment.material ? 0.0f : 1.0f;
				}

				return 0.0f;
			}

		}
	}
}