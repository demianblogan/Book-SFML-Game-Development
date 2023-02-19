#include "Entity.h"

void Entity::UpdateCurrent(sf::Time deltaTime)
{
	sf::Vector2f offset = velocity * deltaTime.asSeconds();
	move(offset);
}

void Entity::SetVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Entity::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Entity::Accelerate(sf::Vector2f velocity)
{
	this->velocity += velocity;
}

void Entity::Accelerate(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

sf::Vector2f Entity::GetVelocity() const
{
	return velocity;
}
