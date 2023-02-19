#pragma once

#include <cassert>
#include <functional>
#include "../SceneNodes/SceneNode.h"

// Command is a structure that agreggates function and its category.
// Every game command is a function with its category.
struct Command
{
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category = (unsigned int)SceneNode::Category::None;
};

// Since we often work on entities that are classes derived from SceneNode, the constant
// need for downcasts is annoying. It would be much more user friendly if we could
// directly create a function with the signature of specific child class. So we provide
// this small adapter that takes a function on a derived class and converts it to a 
// function on the SceneNode base class.
template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> GetDerivedAction(Function function)
{
	auto derivedFunction = [=](SceneNode& node, sf::Time deltaTime)
	{
		// Check if cast is safe:
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it:
		function(static_cast<GameObject&>(node), deltaTime);
	};

	return derivedFunction;
}