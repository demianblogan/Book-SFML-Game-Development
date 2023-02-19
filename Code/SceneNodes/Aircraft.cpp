#include "Aircraft.h"

#include "../Utilities/Utilities.h"

Textures::ID ConvertToTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Type::Eagle:
		return Textures::ID::Eagle;

	case Aircraft::Type::Raptor:
		return Textures::ID::Raptor;

	default:
		return Textures::ID::None;
	}
}

void Aircraft::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Aircraft::Aircraft(Type type, const TextureHolder& textureHolder)
	: type(type)
	, sprite(textureHolder.Get(ConvertToTextureID(type)))
{
	CenterSFMLAssetOrigin(sprite);
}

unsigned int Aircraft::GetCategory() const
{
	switch (type)
	{
	case Aircraft::Type::Eagle:
		return (unsigned int)Category::PlayerAircraft;

	default:
		return (unsigned int)Category::EnemyAircraft;
	}
}