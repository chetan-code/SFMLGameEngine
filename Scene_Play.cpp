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
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::Space, "JUMP");


	m_entities = EntityManager();
	std::cout << "Initializing play scene" << std::endl;
	
	//backgroundLayer - test
	for (int k = 0; k < 5; k++) {
		for (int l = 0; l < 5; l++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					auto e = m_entities.addEntity("bg");
					e->addComponent<CTransform>(Vec2((k * 96) + (i * 24),(l* 72) + j * 24), Vec2(0, 0), 0);
					e->addComponent<CSprite>(gameEngine->getAssets().getTexture("bg"), sf::IntRect(24 * i, 24 * j, 24, 24));
				}
			}
		}
	}


	//enironment layer - test
	for (int i = 0; i < 20; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2(i * 18 * 3, 204), Vec2(0, 0), 0);
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(18, 0, 54, 18));
	}

	//player layer
	m_player = m_entities.addEntity("player");
	m_player->addComponent<CInput>();
	m_player->addComponent<CGravity>(1.0f);
	m_player->addComponent<CTransform>(Vec2(20,180), Vec2(1, 0), 0);
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
			//std::cout << "RIGHT ACTION START" << std::endl;
			HandleInput(Vec2(1, 0));
		}

		if (action.getName() == "LEFT") {
			HandleInput(Vec2(-1, 0));
		}

		if (action.getName() == "JUMP") {
			std::cout << "JUMP START" << std::endl;

			Jump(true);
		}
	}

	if (action.getType() == "END") {
		if (action.getName() == "RIGHT") {
			//std::cout << "RIGHT ACTION END" << std::endl;
			HandleInput(Vec2(0, 0));
		}
		if (action.getName() == "LEFT") {
			HandleInput(Vec2(0, 0));
		}

		if (action.getName() == "JUMP") {
			Jump(false);

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

void Scene_Play::Jump(bool start)
{
	if (start && m_isGrounded) {
		//todo : check if grounded
		m_player->getComponent<CTransform>().velocity.y -= 48;
		m_isGrounded = false;
	}
}



void Scene_Play::sMovement()
{
	//update pos of all entities - using the velocity
	for (auto& e : m_entities.getEntities()) {
		
		//apply movement
		if (e->hasComponent<CTransform>()) {
			Vec2 velocity;
			auto& transform = e->getComponent<CTransform>();
			if (e->hasComponent<CInput>()) {
				//movement with input
				velocity.x = e->getComponent<CInput>().axis.x;
				velocity.y = transform.velocity.y;
				
			}

			if (e->hasComponent<CGravity>()) {
				velocity.y = e->getComponent<CGravity>().gravity;
			}

			//ground check - will be replaced by collider logic
			float groundY = gameEngine->getWindow().getSize().y - 24;
			if (transform.pos.y >= groundY) {
				velocity.y = 0;
				m_isGrounded = true;
			}
			else {
				m_isGrounded = false;
			}


			//apply velocity
			transform.pos += transform.velocity;
			transform.velocity = velocity;
		}


	}
}
