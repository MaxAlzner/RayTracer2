#ifndef RAY_LUMINATION_H
#define RAY_LUMINATION_H

namespace RAY_NAMESPACE
{
	namespace DataObjects
	{

		class RAY_API Lumination
		{
		public:

			inline Lumination() :
				diffuse(0.0f),
				specular(0.0f) {}
			inline Lumination(const float diffuse, const float specular) :
				diffuse(diffuse),
				specular(specular) {}
			inline Lumination(const Color& diffuse, const Color& specular) :
				diffuse(diffuse),
				specular(specular) {}
			inline ~Lumination() {}

			inline Lumination operator+() const;
			inline Lumination operator-() const;
			inline void operator+=(const Lumination& l0);
			inline void operator-=(const Lumination& l0);
			inline void operator*=(const Lumination& l0);
			inline void operator/=(const Lumination& l0);

			Color diffuse;
			Color specular;

		};

		inline RAY_API Lumination operator+(const Lumination& l0, const Lumination& l1);
		inline RAY_API Lumination operator+(const Lumination& l, const float v);
		inline RAY_API Lumination operator+(const float v, const Lumination& l);
		inline RAY_API Lumination operator-(const Lumination& l0, const Lumination& l1);
		inline RAY_API Lumination operator-(const Lumination& l, const float v);
		inline RAY_API Lumination operator-(const float v, const Lumination& l);
		inline RAY_API Lumination operator*(const Lumination& l0, const Lumination& l1);
		inline RAY_API Lumination operator*(const Lumination& l, const float v);
		inline RAY_API Lumination operator*(const float v, const Lumination& l);
		inline RAY_API Lumination operator/(const Lumination& l0, const Lumination& l1);
		inline RAY_API Lumination operator/(const Lumination& l, const float v);
		inline RAY_API Lumination operator/(const float v, const Lumination& l);

	}
}

#endif