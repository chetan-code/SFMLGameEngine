#pragma once
#include "Animation.h"
#include "sfml/Audio.hpp"
class Assets
{
	//This class is used to load all types of assets for the game [at beginning of game].
	//for any new type of asset you may need to add another map.

private:
	std::map <std::string, sf::Texture> textures;
	std::map<std::string, Animation> animations;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::Font> fonts;

public:
	void addTexture(std::string name, std::string path);
	void addAnimation(std::string name, Animation);
	void addSound(std::string name, sf::Sound);
	void addFont(std::string name, std::string path);
	sf::Texture& getTexture(const std::string& name);
	Animation& getAnimation(std::string& name) const;
	sf::Sound& getSound(std::string& name) const;
	sf::Font& getFont(std::string& name) const;
};

