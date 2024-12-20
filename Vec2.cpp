#include "Vec2.h"

float Vec2::length() const
{
	return 0;
}

void Vec2::normalize()
{

}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator*(const float value) const
{
	return Vec2(x * value, y * value);
}
