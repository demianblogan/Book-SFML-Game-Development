#pragma once

#include "../SceneNodes/SceneNode.h"

// SpriteNode is a class that doesn't have only everything that SceneNode, but
// also extra thing - sprite. SceneNode can't been drawn by itself due to absence
// of SFML drawable classes, but SpriteNode has.
class SpriteNode : public SceneNode
{
private:
	sf::Sprite sprite;

	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle);
};