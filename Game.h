#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig{ int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	sf::RenderWindow m_window; //the window we will draw
	EntityManager m_entities; //vector of entitie to maintain
	sf::Font m_font;
	sf::Text m_text;  //score text drawn to screen
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_paused = false; //whether we update the game logic or not
	bool m_running = false; //whether the game is running

	std::shared_ptr<Entity> m_player;

	void init(const std::string& config);
	void setPause(bool paused);

	//Systems : Entity Position Update
	void sMovement();
	//Systems : User Input
	void sUserInput();
	//Systems : Lifespan
	void sLifespan();
	//Systems : Render /Drawing
	void sRender();
	//Systems : Spawn Enemies
	void sEnemySpawner();
	//Systems : Collision
	void sCollision();

	//Helper functions
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public :
	Game(const std::string& config); //constructor, take in game config

	void run();

};

