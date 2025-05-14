#pragma once
#include "EntityManager.h"
#include "Action.h"
#include "GameEngine.h";
class Scene
{
	//this is a abtract base class for all scenes
protected:
	std::map<int, std::string> m_actionMap;//map of keycode and actionName
public :	
	GameEngine* gameEngine;
	EntityManager m_entities; //each scene should assign a new entity manager at initialisation
	int currentFrame;
	
	bool pause;
	bool hasEnded;

	Scene(GameEngine* eng) : gameEngine(eng) {}

	virtual void update();
	virtual void sDoAction(const Action& action);
	virtual void sRender();
	virtual void simulate(int frame);
	void registerAction(int keyCode,const std::string& actionName);
	const std::map<int, std::string>& getActionMap() const;
};

