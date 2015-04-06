
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		using namespace Object::Image;

		inline RAY_API Color TextureFilter::sample(const vec2& texcoord)
		{
			if (this->surface != 0)
			{
				box increment(texcoord, 1.0f / float(this->surface->width()), 1.0f / float(this->surface->height()));

				int x = int(texcoord.x * float(this->surface->width()));
				int y = int(texcoord.y * float(this->surface->height()));
				Color s0 = PackPixel(this->surface->get(x, y), this->surface->format());

				return s0;
			}

			return Color(0.0f);
		}

	}
}