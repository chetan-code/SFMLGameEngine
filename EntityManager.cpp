#include "EntityManager.h"

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	//called by update - remove all dead entites - not active set to false
}

void EntityManager::update()
{
	//add/remove entities

	//clear added entities from m_entities to add

	// remove dead entities

	//remove dead entities from map
	for (auto& [tag, entityVec] : m_entityMap) {
		removeDeadEntities(entityVec);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(e);

	return e;
}
