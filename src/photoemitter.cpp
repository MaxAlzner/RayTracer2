
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
						ray ray = this->_stack->camera->getRay(float(k) / float(this->_photo->_width), float(i) / float(this->_photo->_height));
						RayHit hit;
						Entity* nearest = this->_stack->trace(ray, &hit);

						if (nearest != 0)
						{
							Fragment data(hit, nearest->material);
							this->_photo->_geometrypass.get(k, i) = hit;
							this->_photo->_fragmentpass.get(k, i) = data;
							this->_photo->_lightpass.get(k, i) = this->_stack->albedo(data);
						}
					}
				}
			}
		}

	}
}