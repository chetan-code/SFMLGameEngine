#include "Scene.h"


void Scene::update()
{

}

void Scene::sDoAction(const Action& action)
{
}

void Scene::sRender()
{
}

void Scene::sCamera()
{
}

void Scene::simulate(int frame)
{
}

void Scene::registerAction(int keyCode,const std::string& actionName)
{
	m_actionMap[keyCode] = actionName;
}

const std::map<int, std::string>& Scene::getActionMap() const 
{
	return m_actionMap;
}
