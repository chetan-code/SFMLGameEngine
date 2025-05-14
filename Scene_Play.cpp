#include "Scene_Play.h"
#include <iostream>
#include "sfml/Graphics.hpp"

Scene_Play::Scene_Play(GameEngine* engine, const std::string& levelPath) :
	Scene(engine),
	m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string & levelPath)
{
	registerAction(sf::Keyboard::D, "RIGHT");


	m_entities = EntityManager();
	std::cout << "Initializing play scene" << std::endl;
	//create player
	m_player = m_entities.addEntity("player");
	m_player->addComponent<CInput>();
	m_player->addComponent<CTransform>(Vec2(0,0), Vec2(1, 0), 0);
	m_player->addComponent<CSprite>(gameEngine->getAssets().getTexture("player"), sf::IntRect(0,0,24,24));
}

void Scene_Play::update()
{
	m_entities.update();
	sRender();
	sMovement();
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.getType() == "START") {
		if (action.getName() == "RIGHT") {
			std::cout << "RIGHT ACTION START" << std::endl;
			HandleInput(Vec2(1, 0));
		}
	}

	if (action.getType() == "END") {
		if (action.getName() == "RIGHT") {
			std::cout << "RIGHT ACTION END" << std::endl;
			HandleInput(Vec2(0, 0));
		}
	}
}

void Scene_Play::sRender()
{
	gameEngine->getWindow().clear();
	//draw all entities
	for (auto& e : m_entities.getEntities())
	{
		if (e->getComponent<CTransform>().has || e->getComponent<CSprite>().has) {
			Vec2 pos = e->getComponent<CTransform>().pos;
			e->getComponent<CSprite>().sprite.setPosition(pos.x, pos.y);
			gameEngine->getWindow().draw(e->getComponent<CSprite>().sprite);
		}
	}			

	gameEngine->getWindow().display();
}



void Scene_Play::simulate(int frame)
{
}



void Scene_Play::HandleInput(const Vec2& axis)
{
	m_player->getComponent<CInput>().axis = axis;
}

void Scene_Play::sMovement()
{
	//update pos of all entities - using the velocity
	for (auto& e : m_entities.getEntities()) {
		
		//apply movement
		if (e->getComponent<CTransform>().has) {
			if (e->getComponent<CInput>().has) {
				e->getComponent<CTransform>().pos += e->getComponent<CInput>().axis * e->getComponent<CTransform>().velocity;
			}
			else {
				e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity;
			}
		}
	}
}
