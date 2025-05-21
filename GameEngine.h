#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <sfml/Graphics.hpp>
#include "Assets.h"
#include "Physics.h"
class Scene;

class GameEngine
{
	/*This class is used to manage scenes. 
	Data and systems which are shared across various scenes eg. input and rendering.
	Assets are loaded and accessed from here.
	NOTE : for a larger game engine - you may need to manage asset for individual scenes.
	*/
private: 
	std::map<std::string, std::shared_ptr<Scene>> m_scenes;
	sf::RenderWindow m_window;
	Assets m_assets;
	std::string m_currentScene;
	bool m_running = true;
	Physics m_physics;

public:
	GameEngine(const std::string& configPath);
	void init();
	void update();
	void quit();
	std::shared_ptr<Scene> currentScene();
	void changeScene(const std::string& name,std::shared_ptr<Scene> scene);
	Assets& getAssets();
	Physics& getPhysics();
	sf::RenderWindow& getWindow();
	void sUserInput();
};

