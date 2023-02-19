#pragma once

#include <SFML/Graphics.hpp>

template <typename SFML_AssetType>
void CenterSFMLAssetOrigin(SFML_AssetType& asset)
{
	sf::FloatRect bounds = asset.getLocalBounds();
	asset.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
}