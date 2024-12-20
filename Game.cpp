#include "Game.h"

Game::Game(const std::string& config) {
	init(config);
}


void Game::init(const std::string& config)
{
	//read config file
	//use premade PlayerConfig
	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::setPaused(bool paused)
{
	//TODO
}

void Game::run()
{
	//run game main loop here
	while (m_running) {
		m_entities.update();

		//TODO - pause function

		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();

		//increse the current frame
		//may need to move when pause implement
		m_currentFrame++;
	}
}


void Game::spawnPlayer()
{
	//TODO add prop from config
	
	//auto returns shared pointer
	auto entity = m_entities.addEntity("player");

	//set all components 
	
	//Transform
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1, 1), 0.0f);
	//shape
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(50, 50, 50), 1.0f);
	//input
	entity->cInput = std::make_shared<CInput>()

	//cache player
	m_player = entity;
}

void Game::spawnEnemy()
{
	//spawn enemy using config - similar to player spawn above
	//within bounds

	//record when last enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
	//spawn smaller enemies
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	//param entity - is the one that spawns its
	auto bullet = m_entities.addEntity("bullet");

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	//spawm special weapon on right click
}

void Game::sMovement()
{
	//all entity movement in this function\
	// use player input component to update player 

	//sample speed update
	m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	m_player->cTransform->pos.y += m_player->cTransform->velocity.y;

	//update velocity for enemy and bullets as well
}

void Game::sUserInput()
{
	//todo handle user input

	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		//key pressed 
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				break;
			default:
				break;
			}
		}

		// key is released
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;

			default:
				break;
			}
		}

		//mouse input
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Left mouse button clicked at " << event.mouseButton.x << ":" << event.mouseButton.y << std::endl;
				//shoot bullet
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Right) {
				std::cout << "Right mouse button clicked at " << event.mouseButton.x << ":" << event.mouseButton.y << std::endl;
				//special move
			}
		}
	}
}


void Game::sRender() {
	m_window.clear();

	//set pos and rotation 
	m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);
	m_player->cTransform->angle += 1.0f;
	m_player->cShape->circle.setRotation(m_player->cTransform->angle);
	//draw shape
	m_window.draw(m_player->cShape->circle);

	for (auto& e : m_entities.getEntities())
	{
		//we need to update pos rot etc for all entities
		m_window.draw(e->cShape->circle);
	}

	m_window.display();
}

void Game::sEnemySpawner()
{
	//todo : use m_currentFrame - mLastenemyspawntime to determine how long since last spawn
	spawnEnemy();
}

void Game::sCollision()
{
	//check for collsion between bullet and enemies (get them by tag) - using nested loop
}

