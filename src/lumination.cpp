
#define RAY_EXPORT
#include "..\include\RayTracer.h"

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		inline RAY_API Lumination Lumination::operator+() const
		{
			return Lumination(+this->diffuse, +this->specular);
		}
		inline RAY_API Lumination Lumination::operator-() const
		{
			return Lumination(-this->diffuse, -this->specular);
		}
		inline RAY_API void Lumination::operator+=(const Lumination& l0)
		{
			this->diffuse += l0.diffuse;
			this->specular += l0.specular;
		}
		inline RAY_API void Lumination::operator-=(const Lumination& l0)
		{
			this->diffuse -= l0.diffuse;
			this->specular -= l0.specular;
		}
		inline RAY_API void Lumination::operator*=(const Lumination& l0)
		{
			this->diffuse *= l0.diffuse;
			this->specular *= l0.specular;
		}
		inline RAY_API void Lumination::operator/=(const Lumination& l0)
		{
			this->diffuse /= l0.diffuse;
			this->specular /= l0.specular;
		}

		inline RAY_API Lumination operator+(const Lumination& l0, const Lumination& l1)
		{
			return Lumination(
				l0.diffuse + l1.diffuse,
				l0.specular + l1.specular
				);
		}
		inline RAY_API Lumination operator+(const Lumination& l, const float v)
		{
			return Lumination(
				l.diffuse + v,
				l.specular + v
				);
		}
		inline RAY_API Lumination operator+(const float v, const Lumination& l)
		{
			return Lumination(
				v + l.diffuse,
				v + l.specular
				);
		}
		inline RAY_API Lumination operator-(const Lumination& l0, const Lumination& l1)
		{
			return Lumination(
				l0.diffuse - l1.diffuse,
				l0.specular - l1.specular
				);
		}
		inline RAY_API Lumination operator-(const Lumination& l, const float v)
		{
			return Lumination(
				l.diffuse - v,
				l.specular - v
				);
		}
		inline RAY_API Lumination operator-(const float v, const Lumination& l)
		{
			return Lumination(
				v - l.diffuse,
				v - l.specular
				);
		}
		inline RAY_API Lumination operator*(const Lumination& l0, const Lumination& l1)
		{
			return Lumination(
				l0.diffuse * l1.diffuse,
				l0.specular * l1.specular
				);
		}
		inline RAY_API Lumination operator*(const Lumination& l, const float v)
		{
			return Lumination(
				l.diffuse * v,
				l.specular * v
				);
		}
		inline RAY_API Lumination operator*(const float v, const Lumination& l)
		{
			return Lumination(
				v * l.diffuse,
				v * l.specular
				);
		}
		inline RAY_API Lumination operator/(const Lumination& l0, const Lumination& l1)
		{
			return Lumination(
				l0.diffuse / l1.diffuse,
				l0.specular / l1.specular
				);
		}
		inline RAY_API Lumination operator/(const Lumination& l, const float v)
		{
			return Lumination(
				l.diffuse / v,
				l.specular / v
				);
		}
		inline RAY_API Lumination operator/(const float v, const Lumination& l)
		{
			return Lumination(
				v / l.diffuse,
				v / l.specular
				);
		}

	}
}