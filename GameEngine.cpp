#include <iostream>
#include "GameEngine.h"
#include "Scene_Play.h"

GameEngine::GameEngine(const std::string& configPath)
{
	//we need to load game specific from config file
	init();
}

void GameEngine::init()
{
	std::cout << "Started Engine" << std::endl;
	//load window
	m_window.create(sf::VideoMode(1280, 720), "Game Window");
	m_window.setFramerateLimit(60);
	//load game assets here
	m_assets = Assets();
	m_assets.addTexture("player", "sprites/tilemap_characters.png");
	m_assets.addTexture("environment", "sprites/tilemap_environment.png");
	m_assets.addTexture("bg", "sprites/tilemap_backgrounds.png");
	//set default current scene
	changeScene("play", std::make_shared<Scene_Play>(this, "levelpath.text"));

	update();
}

void GameEngine::update()
{
	//run game main loop here
	while (m_running) {
		sUserInput();
		m_scenes[m_currentScene]->update();
	}
}

void GameEngine::quit()
{
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_scenes[m_currentScene];
}

void GameEngine::changeScene(const std::string& name,std::shared_ptr<Scene> scene)
{
	m_currentScene = name;
	m_scenes[name] = scene;
}

Assets& GameEngine::getAssets()
{
	return m_assets;
}

Physics& GameEngine::getPhysics()
{
	return m_physics;
}

sf::RenderWindow& GameEngine::getWindow()
{
	return m_window;
}

void GameEngine::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		//player mechanics related keys
		//key pressed 
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			
			//if the current scene does not have an action associated with the key , skip the event
			//.find(...) looks for this key in the map.
			//If found, it returns an iterator pointing to the key - value pair.
			//If not found, it returns actionMap.end().
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) {
				continue;
			}

			const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
			
			//look up the action and send the action to the scene
			currentScene()->sDoAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}

		if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
			//adding extra offset for mouse
			int keycode = event.mouseButton.button + 1000;
			//if the current scene does not have an action associated with the key , skip the event
			//.find(...) looks for this key in the map.
			//If found, it returns an iterator pointing to the key - value pair.
			//If not found, it returns actionMap.end().
			if (currentScene()->getActionMap().find(keycode) == currentScene()->getActionMap().end()) {
				continue;
			}

			const std::string actionType = (event.type == sf::Event::MouseButtonPressed) ? "START" : "END";

			//look up the action and send the action to the scene
			currentScene()->sDoAction(Action(currentScene()->getActionMap().at(keycode), actionType));
		}


	}
}
