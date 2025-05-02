#include "Game.h"

Game::Game(const std::string& config) {
	init(config);
}


void Game::init(const std::string& config)
{
	//read config file
	//use premade PlayerConfig
	m_window.create(sf::VideoMode(1280, 720), "Geometry Wars");
	m_window.setFramerateLimit(60);
	//reed font values from config as well
	m_font.loadFromFile("fonts/opensans.ttf");
	m_scoreText.setPosition(10,10);
	m_scoreText.setFont(m_font);
	m_scoreText.setFillColor(sf::Color::White);
	//game over text
	m_gameOverText.setPosition(640, 360);
	m_gameOverText.setFont(m_font);
	m_gameOverText.setFillColor(sf::Color::White);

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
		sUserInput();
		sRender();
		//TODO - pause function
		if (m_gameOver || m_paused) {
			continue;
		}
		sEnemySpawner();
		sMovement();
		sCollision();
		sLifespan();

	

		//increse the current frame
		//may need to move when pause implement
		m_currentFrame++;
	}
}


void Game::spawnPlayer()
{
	//TODO add prop from config
	
	auto entity = m_entities.addEntity("player");

	//set all components 
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(5, 5), 0.0f);
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(255, 0, 0), sf::Color(50, 50, 50), 1.0f);
	entity->cInput = std::make_shared<CInput>();
	entity->cCollision = std::make_shared<CCollision>(32.0f);

	//cache player
	m_player = entity;
}

void Game::spawnEnemy()
{
	//spawn enemy using config - similar to player spawn above
	//within bounds
	float randx = rand() % m_window.getSize().x;
	float randy = rand() % m_window.getSize().y;

	auto enemy = m_entities.addEntity("enemy");
	enemy->cTransform = std::make_shared<CTransform>(Vec2(randx, randy), Vec2(2, 2), 0.1f);
	enemy->cShape = std::make_shared<CShape>(15, 3, sf::Color(0, 255, 0), sf::Color(0, 0, 255), 5);
	enemy->cCollision = std::make_shared<CCollision>(15);

	//record when last enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::restartGame() {
	if (!m_gameOver) { return; }
	//clear all entities
	for (auto& e : m_entities.getEntities()) {
		e->destroy();
	}
	//resetting data 
	m_score = 0;
	m_life = 3;
	spawnPlayer();
	m_gameOver = false;
	m_paused = false;//in case he paused by mistake
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
	//spawn smaller enemies
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	//param entity - is the one that spawns its
	auto bullet = m_entities.addEntity("bullet");
	float bulletSpeed = 15; //TODO - read from config
	Vec2 bulletVelocity = (mousePos - entity->cTransform->pos).normalize() * bulletSpeed;
	//add components to the bullet
	bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, bulletVelocity, 0.0f);
	bullet->cShape = std::make_shared<CShape>(10.0f, 32, sf::Color(255, 255, 255), sf::Color(10, 10, 10), 3.0f);
	bullet->cCollision = std::make_shared<CCollision>(10.0f);
	bullet->cLifespan = std::make_shared<CLifespan>(120);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	//spawm special weapon on right click
}

void Game::sMovement()
{
	//all entity movement in this function\
	// use player input component to update player 
	float verticalAxis = 0;
	float horizontalAxis = 0;
	if (m_player->cInput->up && m_player->cTransform->pos.y - m_player->cCollision->radius > 0) {
		verticalAxis = -1;
	}
	if (m_player->cInput->down && m_player->cTransform->pos.y + m_player->cCollision->radius < m_window.getSize().y) {
		verticalAxis = 1;
	}
	if (m_player->cInput->left && m_player->cTransform->pos.x - m_player->cCollision->radius > 0) {
		horizontalAxis = -1;
	}
	if (m_player->cInput->right && m_player->cTransform->pos.x + m_player->cCollision->radius < m_window.getSize().x) {
		horizontalAxis = 1;
	}
	//sample speed update
	//TODO : multiplying with player own velocity - doesn't seem to work - god knows why? 
	m_player->cTransform->velocity.x = horizontalAxis * 5;
	m_player->cTransform->velocity.y = verticalAxis * 5;
	m_player->cTransform->pos += m_player->cTransform->velocity;
	//update pos of all entities - using the velocity
	for (auto& e : m_entities.getEntities("bullet")) {
		e->cTransform->pos += e->cTransform->velocity;
	}

	//update pos of all entities - using the velocity
	for (auto& enemy : m_entities.getEntities("enemy")) {
		if (enemy->cTransform->pos.x < 0 || enemy->cTransform->pos.x > m_window.getSize().x) {
			enemy->cTransform->velocity.x *= -1;
		}

		if (enemy->cTransform->pos.y < 0 || enemy->cTransform->pos.y > m_window.getSize().y) {
			enemy->cTransform->velocity.y *= -1;
		}
		enemy->cTransform->pos += enemy->cTransform->velocity;
	}
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

		//major game related keys [UI]
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::P:
				m_paused = !m_paused;
				std::cout << "Game Paused :" << m_paused << std::endl;
				break;
			case sf::Keyboard::R:
				restartGame();
				break;
			default:
				break;
			}
		}


		if (m_paused || m_gameOver) {
			continue;
		}

		//player mechanics related keys
		//key pressed 
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = true;
				//std::cout << "W presse" << std::endl;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
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
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
				break;
			default:
				break;
			}
		}

		//mouse input
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Shoot! " << event.mouseButton.x << ":" << event.mouseButton.y << std::endl;
				spawnBullet(m_player,Vec2(event.mouseButton.x, event.mouseButton.y));
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

void Game::sLifespan()
{
	for (auto& bullet : m_entities.getEntities("bullet")) {
		if (!bullet->cLifespan) {
			return;//no lifespan component found - exit
		}

		bullet->cLifespan->remaining--;
		if (bullet->cLifespan->remaining <= 0) {
			bullet->destroy();
			std::cout << "end of bullet life ! bye bye" << std::endl;
		}
	}
}


void Game::sRender() {
	m_window.clear();
	
	//draw all entities
	for (auto& e : m_entities.getEntities())
	{
		
		//set pos and rotation 
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
		//draw shape
		m_window.draw(e->cShape->circle);

	}
	//draw score
	m_scoreText.setString("Score : " + std::to_string(m_score) + " Life: " + std::to_string(m_life));
	m_gameOverText.setString(m_gameOver ? "GAME OVER [R] to restart" : "");
	m_window.draw(m_gameOverText);
	m_window.draw(m_scoreText);
	
	m_window.display();
}

void Game::sEnemySpawner()
{
	//TODO : read spawn time from config
		
	if (m_currentFrame - m_lastEnemySpawnTime > 120) {
		spawnEnemy();
	}
}

void Game::sCollision()
{
	
	//check for collsion between bullet and enemies (get them by tag) - using nested loop
	for (auto& bullet : m_entities.getEntities("bullet")) {
		for (auto& enemy : m_entities.getEntities("enemy")) {
			//component can be null - and can return null ptr - add check
			if (!bullet->cCollision || !enemy->cCollision) {
				//shared_ptr return false if value is not assigned
				return;//no more collision logic
			}

			//collision of bullet and enemy
			if (bullet->cTransform->pos.dist(enemy->cTransform->pos) < (bullet->cCollision->radius + enemy->cCollision->radius)) {
				bullet->destroy();
				enemy->destroy();
				std::cout << "destroy()" << std::endl;
				//increase score
				m_score++;
				std::cout << "Score:" << m_score << std::endl;
			}
		}
	}

	//check for collision between enemy and player
	for (auto& enemy : m_entities.getEntities("enemy")) {
		//component can be null - and can return null ptr - add check
		if (!enemy->cCollision) {
			//shared_ptr return false if value is not assigned
			std::cout << "enemy has no collider" << std::endl;
			return;//no more collision logic
		}

		//std::cout << "distance between player and enemy is : " << enemy->cTransform->pos.dist(m_player->cTransform->pos) << std::endl;
		//Check if collided with player
		if (enemy->cTransform->pos.dist(m_player->cTransform->pos) < (enemy->cCollision->radius + m_player->cCollision->radius)) {
			enemy->destroy();
			m_life--;
			std::cout << "enemy strike player" << std::endl;
			if (m_life <= 0) {
				//game over
				m_gameOver = true;
			}
		}
	}

}

