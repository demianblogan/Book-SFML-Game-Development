#include "SpriteNode.h"

void SpriteNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

SpriteNode::SpriteNode(const sf::Texture& texture)
	: sprite(texture)
{ }

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle)
	: sprite(texture, rectangle)
{ }