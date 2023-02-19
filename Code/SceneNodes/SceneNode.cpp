#include "SceneNode.h"

#include <algorithm>
#include <cassert>
#include "../Commands/Command.h"

void SceneNode::UpdateCurrent(sf::Time deltaTime)
{
	// Do nothing by default. The behaviour should be changed in child classes.
}

void SceneNode::UpdateChildren(sf::Time deltaTime)
{
	for (NodePointer& child : children)
	{
		child->Update(deltaTime);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	DrawCurrent(target, states);
	DrawChildren(target, states);
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Do nothing by default. The behaviour should be changed in child classes.
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const NodePointer& child : children)
	{
		child->draw(target, states);
	}
}

void SceneNode::Update(sf::Time deltaTime)
{
	UpdateCurrent(deltaTime);
	UpdateChildren(deltaTime);
}

sf::Transform SceneNode::GetWorldTransform() const
{
	// Every node contains its own transform. But it a local transform.
	// To convert it into world transform, we multiply it by every next parent node.
	// In the end we will get the "world" transform.

	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::GetWorldPosition() const
{
	// Convert sf::Transform to sf::Vector2f:
	return GetWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::GetCategory() const
{
	return (unsigned int)Category::Scene;
}

void SceneNode::OnCommand(const Command& command, sf::Time deltaTime)
{
	// Check is the command category is the same as the class's.
	if (command.category & GetCategory())
	{
		// Execute this command by sending this object.
		command.action(*this, deltaTime);
	}

	// Command children:
	for (const NodePointer& child : children)
	{
		child->OnCommand(command, deltaTime);
	}
}

void SceneNode::AttachChild(NodePointer child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::NodePointer SceneNode::DetachChild(const SceneNode& node)
{
	// Search the node:
	auto predicate = [&](NodePointer& pointer) { return pointer.get() == &node; };
	auto foundNode = std::find_if(children.begin(), children.end(), predicate);
	assert(foundNode != children.cend());

	// Detach the node:
	NodePointer detachedNode = std::move(*foundNode);
	detachedNode->parent = nullptr;
	children.erase(foundNode);

	return detachedNode;
}