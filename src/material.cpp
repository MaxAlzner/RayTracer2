
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
					return this->color->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
				}

				return Color(1.0f);
			}
			inline RAY_API vec3 Material::surfaceNormal(const vec2& texcoord) const
			{
				if (this->normal != 0)
				{
					vec4 sample = this->normal->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
					return Math::normalize(vec3((sample * 2.0f) - 1.0f));
				}

				return vec3(0.0f, 0.0f, 1.0f);
			}
			inline RAY_API Color Material::surfaceSpecular(const vec2& texcoord) const
			{
				if (this->specular != 0)
				{
					return this->specular->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
				}

				return Color(1.0f);
			}
			inline RAY_API float Material::surfaceTransparency(const vec2& texcoord) const
			{
				if (this->transparency != 0)
				{
					Color sample = this->transparency->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
					return (sample.r + sample.g + sample.b) / 3.0f;
				}

				return 0.0f;
			}
			inline RAY_API float Material::surfaceReflectivity(const vec2& texcoord) const
			{
				if (this->reflect != 0)
				{
					Color sample = this->reflect->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
					return (sample.r + sample.g + sample.b) / 3.0f;
				}

				return 1.0f;
			}
			inline RAY_API Color Material::surfaceEmissive(const vec2& texcoord) const
			{
				if (this->emissive != 0)
				{
					return this->emissive->sample(texcoord, TextureFilter::SAMPLE_LINEAR);
				}

				return Color(0.0f);
			}

		}
	}
}