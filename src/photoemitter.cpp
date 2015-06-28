
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Tracer
	{
		using namespace DataObjects;

		RAY_API void PhotoEmitter::emit()
		{
			const int sampleSpan = (int)pow(2.0, this->_photo->multiSampleDepth);
			const float sampleAtten = 1.0f / float(sampleSpan * sampleSpan);
			if (this->_photo != 0 && this->_stack != 0)
			{
				for (int i = this->_area.p0.y; i < this->_area.p1.y; i++)
				{
					for (int k = this->_area.p0.x; k < this->_area.p1.x; k++)
					{
						Lumination albedo;
						for (int n = 0; n < sampleSpan; n++)
						{
							for (int m = 0; m < sampleSpan; m++)
							{
								albedo += this->cast(
									(float(k) + (float(m) / float(sampleSpan))) / float(this->_photo->_width),
									(float(i) + (float(n) / float(sampleSpan))) / float(this->_photo->_height)
									) * sampleAtten;
							}
						}

						this->_photo->_lightpass.get(k, i) = albedo;
					}
				}
			}
		}

		RAY_API Lumination PhotoEmitter::cast(const float u, const float v)
		{
			Lumination albedo;
			ray r = this->_stack->camera->getRay(u, v);
			RayHit hit;
			Fragment frag = this->_stack->trace(r, &hit);

			if (frag.material != 0)
			{
				TracePath* path = new TracePath;
				*path = frag;

				TracePath* current = path;
				ray lastRay = r;
				for (int n = 1; n <= this->_photo->reflectDepth; n++)
				{
					current->_reflection = new TracePath;
					current->_depth = n;
					ray reflected = current->_fragment.reflect(lastRay);
					Fragment reflection = this->_stack->trace(reflected, 0);
					*(current->_reflection) = reflection;
					if (reflection.material == 0)
					{
						break;
					}

					current = current->_reflection;
					lastRay = reflected;
				}

				albedo = this->_stack->albedo(*path);
				delete path;
			}

			return albedo;
		}

	}
}