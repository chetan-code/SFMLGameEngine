#pragma once
#include "Entity.h"
#define EntityVec std::vector<std::shared_ptr<Entity>>
class EntityManager
{
private:
	EntityVec m_entities;
	EntityVec m_entitiesToAdd;
	std::map<std::string,EntityVec>  m_entityMap;

	void update();

	void removeDeadEntities(EntityVec& vec);

	std::shared_ptr<Entity> addEntity(const std::string& tag);

	const EntityVec& getEntities();

	const EntityVec& getEntities(const std::string& tag);


};

