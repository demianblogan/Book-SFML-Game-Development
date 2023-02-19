#pragma once

#include <array>
#include "ResourceHolder.h"
#include "../Commands/CommandQueue.h"
#include "../SceneNodes/Aircraft.h"
#include "../SceneNodes/SceneNode.h"

// World is a class that represents the game world by itself:
// it loads and holds resources (such as textures and fonts),
// build scene, manages scene graph and command queue, etc.
class World : private sf::NonCopyable
{
private:
	enum class Layer
	{
		Background,
		Air,
		LayerCount
	};

	sf::RenderWindow& window;
	sf::View worldView;

	TextureHolder textureHolder;
	sf::String textureEaglePath = "Media/Textures/Eagle.png";
	sf::String textureRaptorPath = "Media/Textures/Raptor.png";
	sf::String textureDesertPath = "Media/Textures/Desert.png";

	SceneNode sceneGraph;
	std::array<SceneNode*, (size_t)Layer::LayerCount> sceneLayers;
	CommandQueue commandQueue;

	float worldHeight = 2000.0f;
	sf::FloatRect worldBounds;
	float cameraScrollSpeed = -50.0f;
	float distanceToWindowBorders = 40.0f;

	sf::Vector2f playerSpawnPosition;
	Aircraft* playerAircraft = nullptr;

	void LoadTextures();
	void BuildScene();
	void AdaptPlayerPosition();
	void AdaptPlayerVelocity();

public:
	explicit World(sf::RenderWindow& window);

	void Update(sf::Time deltaTime);
	void Draw();

	CommandQueue& GetCommandQueue();
};