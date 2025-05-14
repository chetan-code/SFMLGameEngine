#pragma once
#include <string>
class Action
{
	//This class manages actions(reaction to a input) - each action has unique name and type
	//NOTE : we can use Enum to define action names or types rather than strings - it will be a better approach
	//here we are reducing performance for more readability - but it is not limiting for a small engine
private:
	std::string m_name;
	std::string m_type;
public:
	Action(const std::string& name, const std::string& type) : m_name(name), m_type(type) {}
	const std::string& getName() const;
	const std::string& getType() const;
};

