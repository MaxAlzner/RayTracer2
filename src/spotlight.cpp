
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

			inline RAY_API Lumination SpotLight::luminance(const Fragment& fragment)
			{
				if (fragment.material == 0)
				{
					return Lumination(Color(1.0f, 0.0f, 1.0f), Color(0.0f));
				}

				vec3 l = this->object->transform->position - fragment.position;
				float d = glm::length(l);
				l = normalize(l);

				float atten = min(this->intensity / d, 1.0f);
				float theta = 1.0f - clamp(this->angle / 180.0f, 0.0f, 1.0f);
				float t = dot(l, this->object->transform->forward);

				float penumbra = (t - theta) / (1.0f - theta);

				Lighting data(l, this->occlusion(fragment) * atten * penumbra);

				return t >= theta ?
					fragment.material->shade(data, fragment) :
					Lumination(Color(0.0f), Color(0.0f));
			}

			inline RAY_API float SpotLight::occlusion(const Fragment& fragment)
			{
				if (fragment.material != 0)
				{
					vec3 toLight = this->object->transform->position - fragment.position;
					ray to(fragment.position, normalize(toLight), glm::length(toLight));

					float average = 0.0f;
					Fragment occluded;
					occluded = this->object->stack->trace(ray(fragment.position, normalize(toLight), glm::length(toLight)), 0);
					average += occluded.material != 0 && occluded.material != fragment.material ? 0.0f : 1.0f;

					return average == 0.0f ? 0.0f : average;
				}

				return 0.0f;
			}

		}
	}
}