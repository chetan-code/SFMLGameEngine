#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform {

public :
	Vec2 pos = { 0.0, 0.0};
	Vec2 velocity = { 0.0, 0.0 };
	float angle = 0;

	CTransform(const Vec2& p, const Vec2& v, float a) 
		: pos(p), velocity(v), angle(a) {}
};


class CShape {
public :
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color& fill,
		const sf::Color& outline, float thickness) {
		
		circle.setOrigin(radius, radius);//shifting anchor from top left to center
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setFillColor(fill);
	}
};

class CCollision {
public:
	float radius = 0;
	CCollision(float r) : radius(r) {}
};

class CScore {
public:
	int score = 0;
	CScore(int s) : score(s) {}
};

class CLifespan {
public:
	int remaining = 0;//amount of lifespan remaining on the entity
	int total = 0;//total intial amount of lifespan
	CLifespan(int total) : remaining(total), total(total) {}
};

class CInput {
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput() {}
};




