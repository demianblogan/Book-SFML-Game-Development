#pragma once

#include "SceneNode.h"

// Every movable visual thing on the scene is an entity. So the class
// Entity is a base class for every visual movable thing on screen.
// And since every thing will be drawn on scene - it's the scene node too.
class Entity : public SceneNode
{
private:
	sf::Vector2f velocity;

	virtual void UpdateCurrent(sf::Time deltaTime) override;

public:
	void SetVelocity(const sf::Vector2f& velocity);
	void SetVelocity(float x, float y);
	void Accelerate(sf::Vector2f velocity);
	void Accelerate(float x, float y);
	sf::Vector2f GetVelocity() const;
};