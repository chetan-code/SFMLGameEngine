#include "Vec2.h"
#include <math.h>
#include <iostream>

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const 
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float value) const 
{
	return Vec2(x * value, y * value);
}

Vec2 Vec2::operator / (const float value) const
{
	return Vec2(x / value, y / value);
}

bool Vec2:: operator == (const Vec2& rhs) const 
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2:: operator != (const Vec2& rhs) const {
	return (x != rhs.x && y != rhs.y);
}

void Vec2::operator +=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator*=(const float val)
{
	x *= val;
	y *= val;
}

void Vec2::operator /= (const float val)
{
	x /= val;
	y /= val;
}

float Vec2::length() const
{
	return sqrtf((x * x) + (y * y));
}

Vec2 Vec2::normalize() {
	float magnitude = sqrtf((x * x) + (y * y));
	return Vec2(x / magnitude, y / magnitude);
}


void Vec2::print()
{
	std::cout << x << "," << y << std::endl;
}




