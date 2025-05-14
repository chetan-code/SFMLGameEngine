#include "Animation.h"
#include <string>
#include <cmath>
#include <sfml/Graphics.hpp>
#include "Vec2.h"

Animation::Animation()
{
}

Animation::Animation(const std::string & name, sf::Texture & t, int frameCount, int speed) :
	m_name(name),
	m_sprite(t),
	m_frameCount(frameCount),
	m_currentFrame(0),
	m_speed(speed)
{
	//size of each individual frame sprite inside the animation spriteSheet
	m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));
}

void Animation::update(){
	m_currentFrame++;
	//loop over animation frames
}

bool Animation::hasEnded() const{
	//when animation is at last frame - for non repeating animations
	return true;
}

const std::string & Animation::getName() const{
	return m_name;
}

const Vec2 & Animation::getSize() const{
	return m_size;
}

const sf::Sprite & Animation::getSprite() const{
	return m_sprite;
}

