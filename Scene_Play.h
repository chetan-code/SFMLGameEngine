#pragma once
#include "Scene.h"

class Scene_Play : public Scene{

	struct PlayerConfig {

		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string WEAPON;
	};
private:
	std::string m_levelPath;
	std::shared_ptr<Entity> m_player;
	PlayerConfig m_playerConfig;
	bool m_isGrounded = false;
public :
	Scene_Play(GameEngine* engine, const std::string& levelPath);
	virtual void update() override;
	void init(const std::string& levelPath);
	void loadLevel(const std::string& filename);
	// Inherited via Scene
	virtual void sDoAction(const Action& action) override;
	virtual void sRender() override;
	virtual void simulate(int frame) override;
	//scene specific systems
	void HandleInput(const Vec2& axis);
	void Jump(bool start);
	void sMovement();
	void sCollision();
	void spawnPlayer();
	void playerReset();
	void spawnRandom();
};

