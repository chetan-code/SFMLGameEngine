#include "EntityManager.h"

void EntityManager::update()
{
	//TODO : Add entities from m_entitiesToAdd to the proper location(s)
	// - add them to the vector of all entities
	// - add them to the vecto inside te map, with the tag as a key
	for (auto e : m_entitiesToAdd) {
		m_entities.push_back(e);
	}

	m_entitiesToAdd.clear();

	//remove dead entities from the vector fo all entities
	removeDeadEntities(m_entities);

	//remove dead entities from each vector in the entity map
	//c++17 way of iterating throug [key, value] pairs in map
	for (auto& [tag, entityVec] : m_entityMap) {
		removeDeadEntities(entityVec);
	}

}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	//remove all dead entities from the input vector
	// this is called by update() function
}


std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {

	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	
	m_entitiesToAdd.push_back(entity);

	return entity;
}

const EntityVec& EntityManager::getEntities(){
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag) {
	//this is incorret
	//return proper ec as per tag
	return m_entityMap[tag];
}
