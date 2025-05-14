#include "Assets.h"
#include <iostream>

void Assets::addTexture(std::string name, std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path)) {
		std::cout << "error loading texcture at " << path << std::endl;
		return;
	}
	textures[name] = texture;
}

sf::Texture& Assets::getTexture(const std::string& name)
{
	return textures[name];
}
