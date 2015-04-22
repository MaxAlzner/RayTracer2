
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace DataObjects;

		RAY_API void PhotoEmitter::emit()
		{
			if (this->_photo != 0 && this->_stack != 0)
			{
				for (int i = this->_area.p0.y; i < this->_area.p1.y; i++)
				{
					for (int k = this->_area.p0.x; k < this->_area.p1.x; k++)
					{
						ray r = this->_stack->camera->getRay(float(k) / float(this->_photo->_width), float(i) / float(this->_photo->_height));
						RayHit hit;
						Fragment frag = this->_stack->trace(r, &hit);

						if (frag.material != 0)
						{
							TracePath* path = &this->_photo->_geometrypass.get(k, i);
							*path = frag;

							TracePath* current = path;
							ray lastRay = r;
							for (int n = 1; n <= this->_photo->reflectDepth; n++)
							{
								current->_reflection = new TracePath;
								current->_depth = n;
								ray reflectedRay = current->_fragment.reflect(lastRay);
								Fragment reflection = this->_stack->trace(reflectedRay, 0);
								*(current->_reflection) = reflection;
								if (reflection.material == 0)
								{
									break;
								}

								current = current->_reflection;
								lastRay = reflectedRay;
							}

							this->_photo->_lightpass.get(k, i) = this->_stack->albedo(*path);
						}
					}
				}
			}
		}

	}
}