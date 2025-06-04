#include "Scene_Play.h"
#include <iostream>
#include "sfml/Graphics.hpp"
#include "Physics.h"
#define PIXEL_SIZE 64

Scene_Play::Scene_Play(GameEngine* engine, const std::string& levelPath) :
	Scene(engine),
	m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string & levelPath)
{
	setupView();
	registerInputActions();
	m_entities = EntityManager();
	std::cout << "Initializing play scene" << std::endl;
	setupTestLevel();
	spawnPlayer();
}

void Scene_Play::setupView()
{
	m_cameraType = CameraType::FollowX;
	//view as same size as window
	m_view = sf::View(sf::FloatRect(0, 0, gameEngine->getWindow().getSize().x, gameEngine->getWindow().getSize().y));
	// set viewport - where in window the view will be drawn
	m_view.setViewport(sf::FloatRect(0.25, 0.25, 0.5, 0.5));
	//apply view
	gameEngine->getWindow().setView(m_view);
}

void Scene_Play::registerInputActions()
{
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::Space, "JUMP");
	registerAction(sf::Keyboard::Escape, "RESET");
	registerAction(sf::Mouse::Button::Left + 1000, "MOUSE1");
}

void Scene_Play::setupTestLevel()
{

	//enironment layer - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2(i * PIXEL_SIZE, 400), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(PIXEL_SIZE, PIXEL_SIZE));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE));
	}
	//enironment layer2 - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2((5 * PIXEL_SIZE) + i * PIXEL_SIZE, 450), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(PIXEL_SIZE, PIXEL_SIZE));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE));
	}

	//enironment layer top - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2((7 * PIXEL_SIZE) + i * PIXEL_SIZE, 250), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(PIXEL_SIZE, PIXEL_SIZE));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE));
	}

	//enironment layer3 - test
	for (int i = 0; i < 5; i++) {
		auto e = m_entities.addEntity("tile");
		e->addComponent<CTransform>(Vec2((11 * PIXEL_SIZE) + i * PIXEL_SIZE, (i % 2 == 0) ? 450 : 400), Vec2(0, 0), 0);
		e->addComponent<CBoundingBox>(Vec2(PIXEL_SIZE, PIXEL_SIZE));
		e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE));
	}
}

void Scene_Play::spawnPlayer()
{
	//player layer
	m_player = m_entities.addEntity("player");
	m_player->addComponent<CInput>();
	m_player->addComponent<CGravity>(1.0f);
	m_player->addComponent<CTransform>(Vec2(20, 20), Vec2(1, 0), 0);
	m_player->addComponent<CBoundingBox>(Vec2(48, 80));
	m_player->addComponent<CState>("player_idle");
	//player animation
	m_animationMap["player_idle"] = std::make_shared<Animation>("player_idle", gameEngine->getAssets().getTexture("player_idle"), 1, 1, 20);
	m_animationMap["player_walk"] = std::make_shared<Animation>("player_walk", gameEngine->getAssets().getTexture("player_walk"), 2, 1, 10);
	m_animationMap["player_jump"] = std::make_shared<Animation>("player_jump", gameEngine->getAssets().getTexture("player_jump"), 1, 1, 20);
	m_player->addComponent<CAnimation>(*m_animationMap["player_idle"]);
}


void Scene_Play::update()
{
	m_entities.update();
	sRender();
	sMovement();
	sCollision();
	sCamera();
	checkForStateChange();
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.getType() == "START") {
		if (action.getName() == "RIGHT") {
			//std::cout << "RIGHT ACTION START" << std::endl;
			HandleInput(Vec2(4, 0));
		}

		if (action.getName() == "LEFT") {
			HandleInput(Vec2(-4, 0));
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
			CTransform& t = e->getComponent<CTransform>();
			e->getComponent<CSprite>().sprite.setPosition(t.pos.x, t.pos.y);
			e->getComponent<CSprite>().sprite.setScale(t.scale.x, t.scale.y);
			gameEngine->getWindow().draw(e->getComponent<CSprite>().sprite);
		}

		if (e->getComponent<CTransform>().has || e->getComponent<CAnimation>().has) {
			CTransform& t = e->getComponent<CTransform>();
			e->getComponent<CAnimation>().currentAnimation.getSprite().setPosition(t.pos.x, t.pos.y);
			e->getComponent<CAnimation>().currentAnimation.getSprite().setScale(t.scale.x, t.scale.y);
			//TODO : need to be moved
			e->getComponent<CAnimation>().currentAnimation.update();
			gameEngine->getWindow().draw(e->getComponent<CAnimation>().currentAnimation.getSprite());
		}
	}			

	gameEngine->getWindow().display();
}


void Scene_Play::sCamera() {
	if (m_cameraType == CameraType::FollowX) {
		m_view.setCenter(sf::Vector2f(m_player->getComponent<CTransform>().pos.x, gameEngine->getWindow().getSize().y/2));
		gameEngine->getWindow().setView(m_view);
	}
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
		m_player->getComponent<CTransform>().velocity.y = -20;
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
				if(finalVelocity.x != 0)transform.scale.x = std::copysign(1, finalVelocity.x); 
			}

			//apply gavity
			if (e->hasComponent<CGravity>()){
				finalVelocity.y += e->getComponent<CGravity>().gravity;
			}

			//window bound check - will be replaced by collider logic
			float groundY = gameEngine->getWindow().getSize().y - 96;
			if (transform.pos.y >= groundY) {
				transform.pos.y = groundY;
				finalVelocity.y = 0;
				m_isGrounded = true;
			}
			else {
				m_isGrounded = false;
			}
			//apply velocity
			transform.prevPos = transform.pos;//cache prev pos
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
				Vec2 prevOverlap = gameEngine->getPhysics().GetPreviousOverlap(a,b);
				//vertical collision
				if (prevOverlap.x > prevOverlap.y && overlap.y > 0 && overlap.x > 0){
					//top to bottom
					if(a->getComponent<CTransform>().velocity.y > 0) {
						a->getComponent<CTransform>().pos.y -= overlap.y;
						a->getComponent<CTransform>().velocity.y = 0;	

					}
					//bottom to top
					if (a->getComponent<CTransform>().velocity.y < 0) {
						a->getComponent<CTransform>().pos.y += overlap.y;
						a->getComponent<CTransform>().velocity.y = 0;
					}
				}
				//horizontal collision
				if (prevOverlap.y > prevOverlap.x  && overlap.x > 0 && overlap.y > 0) {
					//left to right
					if (a->getComponent<CTransform>().velocity.x >  0) {
						a->getComponent<CTransform>().pos.x -= overlap.x;
						a->getComponent<CTransform>().velocity.x = 0;
					}
					//right to left
					if (a->getComponent<CTransform>().velocity.x < 0) {
						a->getComponent<CTransform>().pos.x += overlap.x;
						a->getComponent<CTransform>().velocity.x = 0;
					}
				}
			}
		}
	}

}



void Scene_Play::spawnRandom() {
	sf::Vector2i mousePos = sf::Mouse::getPosition(gameEngine->getWindow());
	sf::Vector2f worldPos = gameEngine->getWindow().mapPixelToCoords(mousePos);
	auto e = m_entities.addEntity("random");
	e->addComponent<CGravity>(1.0f);
	e->addComponent<CTransform>(Vec2(worldPos.x, worldPos.y), Vec2(0, 0), 0);
	e->addComponent<CBoundingBox>(Vec2(PIXEL_SIZE, PIXEL_SIZE));
	e->addComponent<CSprite>(gameEngine->getAssets().getTexture("environment"), sf::IntRect(7 * PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE));
}

//TODO : Not sure if this is the best way to do this?
void Scene_Play::checkForStateChange()
{
	CTransform& pt = m_player->getComponent<CTransform>();
	if (pt.velocity.x != 0 && pt.velocity.y == 0) {
		changeState("player_walk");
	}
	if (!m_isGrounded && pt.velocity.x == 0) {
		//change only when player was in air and not moving
		changeState("player_idle");
		m_isGrounded = true;
	}

	if (!m_isGrounded && pt.velocity.y < 0) {
		changeState("player_jump");
	}
}

void Scene_Play::changeState(std::string newState)
{
	if (m_player->getComponent<CState>().stateName != newState) {
		m_player->getComponent<CState>().stateName = newState;
		m_player->getComponent<CAnimation>().currentAnimation = *m_animationMap[newState];
		std::cout << "New State : " << newState << std::endl;
	}
}

void Scene_Play::playerReset()
{
	m_player->getComponent<CTransform>().pos = Vec2(20, 20);
	for (auto& e : m_entities.getEntities("random")) {
		e->destroy();
	}
}
