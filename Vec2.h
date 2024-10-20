#pragma once
#include <string>
class Vec2
{	
	public :
	  float x;
	  float y;

	  Vec2(float xin, float yin) : x(xin), y(yin) {}

	  bool operator == (const Vec2& rhs) const;
	  bool operator != (const Vec2& rhs) const;

	  //operators
	  Vec2 operator + (const Vec2& rhs ) const;
	  Vec2 operator - (const Vec2& rhs) const;
	  Vec2 operator * (const float value) const;
	  Vec2 operator / (const float value) const;

	  void operator += (const Vec2& rhs);
	  void operator -= (const Vec2& rhs);
	  void operator *= (const float val);
	  void operator /= (const float val);

	  //methods
	  float length() const;
	  Vec2 normalize();
	  void print();
};

