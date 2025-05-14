#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"
class Animation
{
	//this class handles animation - sprite based
	//it will iterate over provided frame based on provided size or speed
private:
	sf::Sprite m_sprite;//NOTE sprite keep only a pointer reference to texture
	int m_frameCount;
	int m_currentFrame;
	int m_speed;
	std::string m_name;
	Vec2 m_size;
public :
	Animation();
	Animation(const std::string & name, sf::Texture & t, int frameCount, int speed);
	void update();
	bool hasEnded() const;//if it is a non looping animation - it will be ended when last frame reached
	const std::string & getName() const;
	const Vec2 & getSize() const;
	const sf::Sprite & getSprite() const;
};

