#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum class ID
	{
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
		ButtonNotSelected,
		ButtonSelected,
		ButtonPressed,
		None
	};
}

namespace Fonts
{
	enum class ID
	{
		Main
	};
}

// ResourceHolder is a class that can hold any SFML resource:
// texture, font, sound, shander, etc.
template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<Resource>> resourceMap;

	void InsertResource(Identifier id, std::unique_ptr<Resource> resource);

public:
	template <typename Parameter>
	void Load(Identifier id, const std::string& filename, const Parameter& secondParameter);
	void Load(Identifier id, const std::string& filename);

	Resource& Get(Identifier id);
	const Resource& Get(Identifier id) const;
};

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

// ---------------------------------- IMPLEMENTATION ----------------------------------
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::InsertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
inline void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter& secondParameter)
{
	auto resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename, secondParameter))
	{
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	InsertResource(std::move(resource));
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename)
{
	auto resource = std::make_unique<Resource>();
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	InsertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.cend());

	return *(found->second);
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.cend());

	return *(found->second);
}