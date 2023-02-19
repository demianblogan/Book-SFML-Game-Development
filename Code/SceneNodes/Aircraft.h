#pragma once

#include "Entity.h"
#include "../Application/ResourceHolder.h"

class Aircraft : public Entity
{
public:
	enum class Type
	{
		Eagle,
		Raptor
	};

private:
	Type type;
	sf::Sprite sprite;

	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit Aircraft(Type type, const TextureHolder& textureHolder);

	virtual unsigned int GetCategory() const override;
};