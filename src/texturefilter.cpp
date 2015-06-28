
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		using namespace Object::Image;

		inline RAY_API Color TextureFilter::sample(const vec2& texcoord, const SAMPLETYPE type)
		{
			if (this->surface != 0)
			{
				if (type == SAMPLE_NEAREST)
				{
					return PackPixel(this->surface->get(int(texcoord.x * float(this->surface->width())), int(texcoord.y * float(this->surface->height()))), this->surface->format());
				}
				else if (type == SAMPLE_LINEAR)
				{
					vec2 increment = 1.0f / vec2(float(this->surface->width()), float(this->surface->height()));
					vec2 uv0 = (texcoord % increment) / increment;
					vec2 uv1 = 1.0f - uv0;
					vec2 linear0 = Math::normalize(uv0) * 0.25f;
					vec2 linear1 = Math::normalize(vec2(uv1.x, uv0.y)) * 0.25f;
					vec2 linear2 = Math::normalize(vec2(uv0.x, uv1.y)) * 0.25f;
					vec2 linear3 = Math::normalize(uv1) * 0.25f;

					int x0 = int(texcoord.x * float(this->surface->width()));
					int y0 = int(texcoord.y * float(this->surface->height()));
					int x1 = Math::min(x0 + 1, this->surface->width());
					int y1 = Math::min(y0 + 1, this->surface->height());

					return
						(PackPixel(this->surface->get(x0, y0), this->surface->format()) * Math::magnitude(linear0)) +
						(PackPixel(this->surface->get(x1, y0), this->surface->format()) * Math::magnitude(linear1)) +
						(PackPixel(this->surface->get(x0, y1), this->surface->format()) * Math::magnitude(linear2)) +
						(PackPixel(this->surface->get(x1, y1), this->surface->format()) * Math::magnitude(linear3));
				}
			}

			return Color(0.0f);
		}

	}
}