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
	std::map<std::string,std::shared_ptr<Animation>> m_animationMap;//map of player state and animation
	bool m_isGrounded = false;
	sf::View m_view;
public :
	Scene_Play(GameEngine* engine, const std::string& levelPath);
	virtual void update() override;
	void init(const std::string& levelPath);
	void setupView();
	void setupTestLevel();
	void registerInputActions();
	void loadLevel(const std::string& filename);
	// Inherited via Scene
	virtual void sDoAction(const Action& action) override;
	virtual void sRender() override;
	virtual void sCamera() override;
	virtual void simulate(int frame) override;
	//scene specific systems
	void HandleInput(const Vec2& axis);
	void Jump(bool start);
	void sMovement();
	void sCollision();
	void spawnPlayer();
	void playerReset();
	void spawnRandom();
	void checkForStateChange();
	void changeState(std::string newState);
};

