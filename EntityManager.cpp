#include "EntityManager.h"
#include <iostream>
#include <algorithm>

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// Remove all even numbers from vector v
	auto ne = remove_if(vec.begin(), vec.end(),
		[](std::shared_ptr<Entity> e) {
			return !e->isActive();
		});
	vec.erase(ne, vec.end());	
}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for (auto& e : m_entitiesToAdd) {
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}

	m_entitiesToAdd.clear();

	//remove dead entities from map
	for (auto& [tag, entityVec] : m_entityMap) {
		removeDeadEntities(entityVec);
	}
	removeDeadEntities(m_entities);
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(e);

	return e;
}

const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
