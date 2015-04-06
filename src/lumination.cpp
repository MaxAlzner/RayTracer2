
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		inline RAY_API void Lumination::operator=(const Lumination& l0)
		{
			this->diffuse = l0.diffuse;
			this->specular = l0.specular;
		}
		inline RAY_API void Lumination::operator+=(const Lumination& l0)
		{
			this->diffuse += l0.diffuse;
			this->specular += l0.specular;
		}

		inline RAY_API Lumination operator+(const Lumination& l0, const Lumination& l1)
		{
			return Lumination(
				l0.diffuse + l1.diffuse,
				l0.specular + l1.specular
				);
		}

	}
}