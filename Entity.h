#pragma once

#include <memory>
#include <string>
#include "Components.h"

//container for components
//some unique data like id tag alive
class Entity
{
	//Entity Manager now can call the private constructor 
	friend class EntityManager;

	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "Default";


	Entity(const size_t id,const std::string& tag);

	public : 
	//components
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;


	//private member access function
	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();

};

