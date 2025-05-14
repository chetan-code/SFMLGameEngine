#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0.0f), y(0.0f)
{
}

Vec2::Vec2(float xin, float yin) : x(xin), y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}


Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}


Vec2 Vec2::operator*(const float value) const
{
	return Vec2(x * value, y * value);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}


Vec2 Vec2::operator/(const Vec2& rhs) const
{
	return Vec2(x / rhs.x , y / rhs.y);
}

Vec2 Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return Vec2(x, y);
}

Vec2 Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return Vec2(x,y);
}

Vec2 Vec2::operator*=(const Vec2& rhs)
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator*=(const float value)
{
	return Vec2(x * value, y * value);
}

Vec2 Vec2::operator/=(const float value)
{
	return Vec2(x / value , y / value);
}

float Vec2::dist(const Vec2 rhs) const
{
	//return distance between two vectors - sweet pythagoras
	return sqrtf((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
}

Vec2 Vec2::normalize()
{
	float mag = sqrtf((x * x) + (y * y));
	//avoid division by zero
	if (mag == 0) {
		return Vec2(0, 0);
	}
	//return unit vector in same direction
	return Vec2(x / mag, y / mag);
}
