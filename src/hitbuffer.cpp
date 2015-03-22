
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace Primitives
	{

		bool HitBuffer::isEmpty() const
		{
			return this->buffer == 0;
		}

		inline RayHit& HitBuffer::get(const int x, const int y)
		{
			return this->buffer[(this->width * (y % this->height)) + (x % this->width)];
		}
		inline RayHit& HitBuffer::get(const int x, const int y, const int z)
		{
			return this->buffer[(this->width * this->height * (z % this->depth)) + (this->width * (y % this->height)) + (x % this->width)];
		}

		inline RayHit& HitBuffer::operator[](const int index)
		{
			return this->buffer[index % this->size];
		}

		void HitBuffer::build()
		{
			if (this->size > 0)
			{
				this->buffer = new RayHit[this->size];
			}
		}
		void HitBuffer::dispose()
		{
			if (this->buffer != 0)
			{
				delete[] this->buffer;
				this->buffer = 0;
			}
		}

	}
}