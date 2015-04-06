
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Components
	{
		namespace Cameras
		{

			RAY_API inline void Camera::adjust(float width, float height)
			{
				this->aperture.x = width;
				this->aperture.y = height;
				this->adjust();
			}
			RAY_API inline void Camera::adjust()
			{
				float x = float(this->aperture.x) / 2.0f;
				float y = float(this->aperture.y) / 2.0f;

				if (this->object != 0)
				{
					this->viewport.p1 = this->object->transform->position + (this->object->transform->right * -x) + (this->object->transform->up * y);
					this->viewport.p2 = this->object->transform->position + (this->object->transform->right * x) + (this->object->transform->up * y);
					this->viewport.p3 = this->object->transform->position + (this->object->transform->right * -x) + (this->object->transform->up * -y);
					this->viewport.p4 = this->object->transform->position + (this->object->transform->right * x) + (this->object->transform->up * -y);
					this->viewport.px = this->viewport.p2 - this->viewport.p1;
					this->viewport.py = this->viewport.p3 - this->viewport.p1;

					this->viewport.focal = this->focalDepth <= 0.0f ?
						this->object->transform->position :
						this->object->transform->position + (this->object->transform->forward * -this->focalDepth);
				}
			}

			RAY_API inline ray Camera::getRay(float u, float v)
			{
				vec3 origin = this->viewport.p1 + (this->viewport.px * u) + (this->viewport.py * v);
				vec3 direction(0.0f, 0.0f, 1.0f);
				if (this->object != 0)
				{
					direction = this->focalDepth <= 0.0f ?
						this->object->transform->forward :
						Math::normalize(origin - this->viewport.focal);
				}

				return ray(origin, direction);
			}
			RAY_API inline ray Camera::getRay(vec2& uv)
			{
				return this->getRay(uv.x, uv.y);
			}

		}
	}
}