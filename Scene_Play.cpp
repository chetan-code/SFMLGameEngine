#include "Scene_Play.h"
#include <iostream>
#include "sfml/Graphics.hpp"
#include "Physics.h"

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
	registerAction(sf::Keyboard::Escape, "RESET");
	registerAction(sf::Mouse::Button::Left + 1000, "MOUSE1");

	m_entities = EntityManager();
	std::cout << "Initializing play scene" << std::endl;
	
	//backgroundLayer - test
	//for (int k = 0; k < 5; k++) {
	//	for (int l = 0; l < 5; l++) {
	//		for (int i = 0; i < 4; i++) {
	//			for (int j = 0; j < 3; j++) {
	//				auto e = m_entities.addEntity("bg");
	//				e->addComponent<CTransform>(Vec2((k * 96) + (i * 24),(l* 72) + j * 24), Vec2(0, 0), 0);
	//				e->addComponent<CSprite>(gameEngine->getAssets().getTexture("bg"), sf::IntRect(24 * i, 24 * j, 24, 24));
	//			}
	//		}
	//	}
	//}


	//enironment layer - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2(i * 18 * 3, 204), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(54, 18));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(18, 0, 54, 18));
	}
	//enironment layer2 - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2((5 * 54) + i * 18 * 3, 224), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(54, 18));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(18, 0, 54, 18));
	}

	//enironment layer3 - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2((11 * 54) + i * 18 * 3, (i % 2 == 0) ? 204 : 224), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(54, 18));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(18, 0, 54, 18));
	}


	spawnPlayer();
}

void Scene_Play::update()
{
	m_entities.update();
	sRender();
	sMovement();
	sCollision();
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.getType() == "START") {
		if (action.getName() == "RIGHT") {
			//std::cout << "RIGHT ACTION START" << std::endl;
			HandleInput(Vec2(2, 0));
		}

		if (action.getName() == "LEFT") {
			HandleInput(Vec2(-2, 0));
		}

		if (action.getName() == "JUMP") {
			Jump(true);
		}

		if (action.getName() == "RESET") {
			playerReset();
		}

		if (action.getName() == "MOUSE1") {
			spawnRandom();
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
	if (start && m_player->getComponent<CTransform>().velocity.y == 0) {
		//todo : check if grounded
		m_player->getComponent<CTransform>().velocity.y = -15;
		m_isGrounded = false;
		std::cout << "JUMP START" << std::endl;

	}
}



void Scene_Play::sMovement()
{
	//update pos of all entities - using the velocity
	for (auto& e : m_entities.getEntities()) {
		
		//apply movement
		if (e->hasComponent<CTransform>()) {
			auto& transform = e->getComponent<CTransform>();
			Vec2 finalVelocity = transform.velocity;
			if (e->hasComponent<CInput>()) {
				//movement with input
				finalVelocity.x = e->getComponent<CInput>().axis.x;		
			}

			//apply gavity
			if (e->hasComponent<CGravity>()){
				finalVelocity.y += e->getComponent<CGravity>().gravity;
			}



			//ground check - will be replaced by collider logic
			float groundY = gameEngine->getWindow().getSize().y - 24;
			if (transform.pos.y >= groundY) {
				transform.pos.y = groundY;
				finalVelocity.y = 0;
				m_isGrounded = true;
			}
			else {
				m_isGrounded = false;
			}
			//apply velocity
			transform.pos += finalVelocity;
			transform.velocity = finalVelocity;
		}


	}
}

void Scene_Play::sCollision()
{
	for (int i = 0; i < m_entities.getEntities().size(); i++) {
		for (int j = 0; j < m_entities.getEntities().size(); j++) {
			auto& a = m_entities.getEntities()[i];
			auto& b = m_entities.getEntities()[j];
			if (a != b && a->hasComponent<CBoundingBox>() && b->hasComponent<CBoundingBox>()) {
				Vec2 overlap = gameEngine->getPhysics().GetOverlap(a, b);
				//vertical overlap
				if (overlap.y > 0 && overlap.x > 0){
					if(a->getComponent<CTransform>().velocity.y != 0) {
						a->getComponent<CTransform>().pos.y -= overlap.y;
						a->getComponent<CTransform>().velocity.y = 0;
						//std::cout << "Overlap = " << overlap.x << ":" << overlap.y << std::endl;
					}
				}
			}
		}
	}

}

void Scene_Play::spawnPlayer()
{
	//player layer
	m_player = m_entities.addEntity("player");
	m_player->addComponent<CInput>();
	m_player->addComponent<CGravity>(1.0f);
	m_player->addComponent<CTransform>(Vec2(20, 20), Vec2(1, 0), 0);
	m_player->addComponent<CBoundingBox>(Vec2(24, 24));
	m_player->addComponent<CSprite>(gameEngine->getAssets().getTexture("player"), sf::IntRect(0, 0, 24, 24));
}

void Scene_Play::spawnRandom() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(gameEngine->getWindow());
	sf::Vector2f worldPos = gameEngine->getWindow().mapPixelToCoords(mousePos);
	auto e = m_entities.addEntity("random");
	e->addComponent<CGravity>(1.0f);
	e->addComponent<CTransform>(Vec2(worldPos.x, worldPos.y), Vec2(0, 0), 0);
	e->addComponent<CBoundingBox>(Vec2(18, 18));
	e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(9*18, 0, 18, 18));
}

void Scene_Play::playerReset()
{
	m_player->getComponent<CTransform>().pos = Vec2(20, 20);
}
