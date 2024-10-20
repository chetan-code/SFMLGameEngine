#include "Game.h"
#include <fstream>

Game::Game(const std::string& config) {
	init(config);
}


void Game::init(const std::string& path)
{
	//read config file
	std::ifstream fin(path);
	//example
	fin >> m_playerConfig.SR >> m_playerConfig.CR;
	
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::run() {
	
	//TODO :
	//add pause funtion in here
	//some function should work while paused (rendering)
	//some function shouldn't work (movement / input)

	//gameloop
	while (m_running) {
		m_entities.update();

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();
		//increase the current frame
		//may need to be moved when pause implemented
		m_currentFrame++;
	}

}

void Game::setPause(bool paused)
{
	//TODO : just change the variable
}

void Game::spawnPlayer() {
	//TODO : finish adding all the properties of the player with the correct values from the config

	//We create every entity by calling EntityManager.addEntity(tag)
	//This returns a std::shared_ptr<Entity>, so we 'auto' to save typing
	auto entity = m_entities.addEntity("player");

	//Give the entity a transform so it spawns at (200, 200) with velocity(1,1) and angle 0
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;//spawning at center
	entity->cTranform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	//the entity shape - radius 32, 8 sides, drak grey full, outline (thickness 4, red)
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255,0,0), 4.0f);

	//add input component to the player so we can control it
	entity->cInput = std::make_shared<CInput>();

	//Since this is our player - we set it as game player variable
	//this is slightly against our entityManager paradigm , but we use player so it worth it
	m_player = entity;
}

void Game::spawnEnemy() {
	
	//spawn player as per config
	//spawn within the border of window

	//same as player spawn

	//record last time enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {
}


void Game::sEnemySpawner() {
	//TODO : spawning code
	//use m_currentFrame - m_lastEnemySpawnTime to detetermine
	// how long it has been since the last enemy spawn
	spawnEnemy();
}

//Systems
void Game::sRender() {

	//TODO : change the code to draw ALL entities
	//sample code to draw player entity

	m_window.clear();

	//set pos of shape based on entity transform pos
	m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
	
	//set rotation of shape based on the entity tranform angle
	m_player->cTransform->angle += 10.0f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	//draw the entity sf::circleShape
	m_window.draw(m_player->cShape->circle);

	//TODO : loop through all entities of entity manager - set pos , rot and draw entities

	m_window.display();
}



