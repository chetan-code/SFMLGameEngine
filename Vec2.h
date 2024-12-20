#pragma once
class Vec2
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float xin, float yin);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const float value) const;
	Vec2 operator / (const Vec2& rhs) const;

	Vec2 operator += (const Vec2& rhs);
	Vec2 operator -= (const Vec2& rhs);
	Vec2 operator *= (const float value);
	Vec2 operator /= (const float value);

	float dist(const Vec2 rhs) const;
	float length() const;
	void normalize();
};

