#pragma once

#include <memory>
#include <string>
#include "Components.h"
#include <tuple>

typedef std::tuple<
	CTransform,
	CLifespan,
	CInput,
	CState,
	CGravity,
	CBoundingBox,
	CAnimation,
	CSprite
> ComponentTuple;


//container for components
//some unique data like id tag alive
class Entity
{
	//Entity Manager now can call the private constructor 
	friend class EntityManager;

	bool m_active = true;
	size_t m_id = 0;
	std::string m_tag = "Default";
	ComponentTuple m_components;

	Entity(const size_t id, const std::string& tag);

//private:

	//components
	//std::shared_ptr<CTransform> cTransform;
	//std::shared_ptr<CShape> cShape;
	//std::shared_ptr<CCollision> cCollision;
	//std::shared_ptr<CInput> cInput;
	//std::shared_ptr<CScore> cScore;
	//std::shared_ptr<CLifespan> cLifespan;
public:
	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();

	template <typename T>
	bool hasComponent() const {
		return getComponent<T>().has;
	}

	template<typename T>
	T& getComponent() {
		return std::get<T>(m_components);
	}

	template<typename T>
	const T& getComponent() const {
		return std::get<T>(m_components);
	}

	template <typename T>
	void removeComponent() {
		getComponent<T>() = T();
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	}

};

