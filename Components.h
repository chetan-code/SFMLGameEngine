#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Component {
public:
	bool has = false;
};


class CTransform : public Component {
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 prevPos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0f, 0.0f };
	float angle = 0;

	CTransform() {}
	CTransform(const Vec2& p, const Vec2& v, float a) :
		pos(p), velocity(v), angle(a) {}

};

class CShape : public Component {

public:
	sf::CircleShape circle;
	CShape() {}
	CShape(float radius, int point, const sf::Color fill,
		const sf::Color& outline, float thickness)
		: circle(radius, point) {
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CSprite : public Component {
public :
	sf::Sprite sprite;
	sf::IntRect rect;
	CSprite() {}
	CSprite(sf::Texture& t, sf::IntRect r) : sprite(t, r), rect(r){}
};

class CCollision : public Component {
public:
	float radius = 0;
	CCollision(){}
	CCollision(float r) : radius(r) {}
};


class CScore : public Component {
public:
	int score = 0;
	CScore() {}
	CScore(int s) : score(s) {}
};

class CLifespan : public Component {
public:
	int remaining = 0;
	int total = 0;
	CLifespan(int total)
		: remaining(total), total(total) {}
	CLifespan() {}
};


class CInput : public Component {
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
	Vec2 axis = {0.0, 0.0};

	CInput() : axis(0.0, 0.0){}
};

class CBoundingBox : public Component {
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox(Vec2 s) : size(s) , halfSize(s.x/2, s.y/2){}
	CBoundingBox() {}
};


class CAnimation : public Component {
public:
	Animation currentAnimation;
	CAnimation() {};
	CAnimation(Animation newAnim) : currentAnimation(newAnim) {}
};

class CState : public Component {
public :
	std::string stateName;
	CState() {};
	CState(const std::string& name) : stateName(name) {}
};

class CGravity : public Component {
public:
	float gravity;
	CGravity() {};
	CGravity(float value) : gravity(value) {}
};