
#include "..\include\MediaLoader.h"

namespace medialoader
{

	inline MEDIALOADERAPI float Color::luminance()
	{
		return ((this->r + this->g + this->b) / 3.0f) * this->a;
	}
		
	inline MEDIALOADERAPI void Color::operator=(const Color& c)
	{
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
		this->a = c.a;
	}
	inline MEDIALOADERAPI void Color::operator=(const float scalar)
	{
		this->r = scalar;
		this->g = scalar;
		this->b = scalar;
	}
	inline MEDIALOADERAPI Color Color::operator+() const
	{
		return Color(+this->r, +this->g, +this->b, +this->a);
	}
	inline MEDIALOADERAPI Color Color::operator-() const
	{
		return Color(-this->r, -this->g, -this->b, -this->a);
	}
	inline MEDIALOADERAPI void Color::operator+=(const Color& c)
	{
		this->r += c.r;
		this->g += c.g;
		this->b += c.b;
		this->a = max(this->a, c.a);
	}
	inline MEDIALOADERAPI void Color::operator+=(const float scalar)
	{
		this->r += scalar;
		this->g += scalar;
		this->b += scalar;
		this->a = max(this->a, scalar);
	}
	inline MEDIALOADERAPI void Color::operator-=(const Color& c)
	{
		this->r -= c.r;
		this->g -= c.g;
		this->b -= c.b;
		this->a = min(this->a, c.a);
	}
	inline MEDIALOADERAPI void Color::operator-=(const float scalar)
	{
		this->r -= scalar;
		this->g -= scalar;
		this->b -= scalar;
		this->a = min(this->a, scalar);
	}
	inline MEDIALOADERAPI void Color::operator*=(const Color& c)
	{
		this->r *= c.r;
		this->g *= c.g;
		this->b *= c.b;
		this->a = max(this->a, c.a);
	}
	inline MEDIALOADERAPI void Color::operator*=(const float scalar)
	{
		this->r *= scalar;
		this->g *= scalar;
		this->b *= scalar;
		this->a = max(this->a, scalar);
	}
	inline MEDIALOADERAPI void Color::operator/=(const Color& c)
	{
		this->r /= c.r;
		this->g /= c.g;
		this->b /= c.b;
		this->a = min(this->a, c.a);
	}
	inline MEDIALOADERAPI void Color::operator/=(const float scalar)
	{
		this->r /= scalar;
		this->g /= scalar;
		this->b /= scalar;
		this->a = min(this->a, scalar);
	}
	inline MEDIALOADERAPI bool Color::operator==(const Color& c) const
	{
		return this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a;
	}
	inline MEDIALOADERAPI bool Color::operator!=(const Color& c) const
	{
		return this->r != c.r && this->g != c.g && this->b != c.b && this->a != c.a;
	}
	inline MEDIALOADERAPI bool Color::operator>(const Color& c) const
	{
		return ((this->r + this->g + this->b) * this->a) > ((c.r + c.g + c.b) * c.a);
	}
	inline MEDIALOADERAPI bool Color::operator<(const Color& c) const
	{
		return ((this->r + this->g + this->b) * this->a) < ((c.r + c.g + c.b) * c.a);
	}
	inline MEDIALOADERAPI bool Color::operator>=(const Color& c) const
	{
		return ((this->r + this->g + this->b) * this->a) >= ((c.r + c.g + c.b) * c.a);
	}
	inline MEDIALOADERAPI bool Color::operator<=(const Color& c) const
	{
		return ((this->r + this->g + this->b) * this->a) <= ((c.r + c.g + c.b) * c.a);
	}
	inline MEDIALOADERAPI Color Color::operator!() const
	{
		return Color(1.0f - clamp(this->r), 1.0f - clamp(this->g), 1.0f - clamp(this->b), 1.0f - clamp(this->a));
	}
	inline MEDIALOADERAPI Color Color::operator&&(const Color& c) const
	{
		return Color(min(this->r, c.r), min(this->g, c.g), min(this->b, c.b), min(this->a, c.a));
	}
	inline MEDIALOADERAPI Color Color::operator||(const Color& c) const
	{
		return Color(max(this->r, c.r), max(this->g, c.g), max(this->b, c.b), max(this->a, c.a));
	}

	inline MEDIALOADERAPI Color operator+(const Color& c0, const Color& c1)
	{
		return Color(c0.r + c1.r, c0.g + c1.g, c0.b + c1.b, c0.a + c1.a);
	}
	inline MEDIALOADERAPI Color operator+(const Color& c, const float v)
	{
		return Color(c.r + v, c.g + v, c.b + v, c.a + v);
	}
	inline MEDIALOADERAPI Color operator+(const float v, const Color& c)
	{
		return Color(v + c.r, v + c.g, v + c.b, v + c.a);
	}
	inline MEDIALOADERAPI Color operator-(const Color& c0, const Color& c1)
	{
		return Color(c0.r - c1.r, c0.g - c1.g, c0.b - c1.b, c0.a - c1.a);
	}
	inline MEDIALOADERAPI Color operator-(const Color& c, const float v)
	{
		return Color(c.r - v, c.g - v, c.b - v, c.a - v);
	}
	inline MEDIALOADERAPI Color operator-(const float v, const Color& c)
	{
		return Color(v - c.r, v - c.g, v - c.b, v - c.a);
	}
	inline MEDIALOADERAPI Color operator*(const Color& c0, const Color& c1)
	{
		return Color(c0.r * c1.r, c0.g * c1.g, c0.b * c1.b, c0.a * c1.a);
	}
	inline MEDIALOADERAPI Color operator*(const Color& c, const float v)
	{
		return Color(c.r * v, c.g * v, c.b * v, c.a * v);
	}
	inline MEDIALOADERAPI Color operator*(const float v, const Color& c)
	{
		return Color(v * c.r, v * c.g, v * c.b, v * c.a);
	}
	inline MEDIALOADERAPI Color operator/(const Color& c0, const Color& c1)
	{
		return Color(c0.r / c1.r, c0.g / c1.g, c0.b / c1.b, c0.a / c1.a);
	}
	inline MEDIALOADERAPI Color operator/(const Color& c, const float v)
	{
		return Color(c.r / v, c.g / v, c.b / v, c.a / v);
	}
	inline MEDIALOADERAPI Color operator/(const float v, const Color& c)
	{
		return Color(v / c.r, v / c.g, v / c.b, v / c.a);
	}

}