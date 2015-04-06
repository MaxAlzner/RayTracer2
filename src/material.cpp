
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Materials
		{

			inline RAY_API Color Material::surfaceColor(const vec2& texcoord) const
			{
				if (this->color != 0)
				{
					return this->color->sample(texcoord);
				}

				return Color(1.0f);
			}
			inline RAY_API vec3 Material::surfaceNormal(const vec2& texcoord) const
			{
				if (this->normal != 0)
				{
					vec4 sample = this->normal->sample(texcoord);
					return Math::normalize(vec3((sample * 2.0f) - 1.0f));
				}

				return vec3(0.0f, 0.0f, 1.0f);
			}
			inline RAY_API float Material::specularIntensity(const vec2& texcoord) const
			{
				if (this->specular != 0)
				{
					return this->specular->sample(texcoord).r;
				}

				return 1.0f;
			}

		}
	}
}