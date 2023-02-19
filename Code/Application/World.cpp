#include "World.h"

#include "../SceneNodes/SpriteNode.h"

void World::LoadTextures()
{
	textureHolder.Load(Textures::ID::Eagle, textureEaglePath);
	textureHolder.Load(Textures::ID::Raptor, textureRaptorPath);
	textureHolder.Load(Textures::ID::Desert, textureDesertPath);
}

void World::BuildScene()
{
	// Initialize the layers:
	for (size_t i = 0; i < (size_t)Layer::LayerCount; i++)
	{
		SceneNode::NodePointer layer(new SceneNode());
		sceneLayers[i] = layer.get();
		sceneGraph.AttachChild(std::move(layer));
	}

	// Prepare the tiled background:
	sf::Texture& backgroundTexture = textureHolder.Get(Textures::ID::Desert);
	sf::IntRect backgroundTextureRectangle(worldBounds);
	backgroundTexture.setRepeated(true);

	// Add the background sprite to the scene:
	auto backgroundSprite = std::make_unique<SpriteNode>(backgroundTexture, backgroundTextureRectangle);
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[(size_t)Layer::Background]->AttachChild(std::move(backgroundSprite));

	// Add player's aircraft:
	auto leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textureHolder);
	playerAircraft = leader.get();
	playerAircraft->setPosition(playerSpawnPosition);
	sceneLayers[(size_t)Layer::Air]->AttachChild(std::move(leader));
}

void World::AdaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least "distanceToWindowBorders" units from the border:
	sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.0f, worldView.getSize());

	sf::Vector2f playerPosition = playerAircraft->getPosition();
	playerPosition.x = std::max(playerPosition.x, viewBounds.left + distanceToWindowBorders);
	playerPosition.x = std::min(playerPosition.x, viewBounds.left + viewBounds.width - distanceToWindowBorders);
	playerPosition.y = std::max(playerPosition.y, viewBounds.top + distanceToWindowBorders);
	playerPosition.y = std::min(playerPosition.y, viewBounds.top + viewBounds.height - distanceToWindowBorders);
	playerAircraft->setPosition(playerPosition);
}

void World::AdaptPlayerVelocity()
{
	sf::Vector2f playerVelocity = playerAircraft->GetVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity):
	if (playerVelocity.x != 0.0f && playerVelocity.y != 0.0f)
	{
		playerAircraft->SetVelocity(playerVelocity / std::sqrt(2.0f));
	}

	// Add scrolling velocity
	playerAircraft->Accelerate(0.f, cameraScrollSpeed);
}

World::World(sf::RenderWindow& window)
	: window(window)
	, worldView(window.getDefaultView())
	, worldBounds(0, 0, worldView.getSize().x, worldHeight)
	, playerSpawnPosition(worldView.getSize().x / 2, worldBounds.height - worldView.getSize().y / 2)
{
	LoadTextures();
	BuildScene();

	worldView.setCenter(playerSpawnPosition);
}

void World::Update(sf::Time deltaTime)
{
	// Scroll the world, reset player velocity:
	worldView.move(0, cameraScrollSpeed * deltaTime.asSeconds());
	playerAircraft->SetVelocity(0, 0);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction):
	while (!commandQueue.IsEmpty())
	{
		sceneGraph.OnCommand(commandQueue.Pop(), deltaTime);
	}
	AdaptPlayerVelocity();

	// Regular update step, adapt position (correct if outside view):
	sceneGraph.Update(deltaTime);
	AdaptPlayerPosition();
}

void World::Draw()
{
	window.setView(worldView);
	window.draw(sceneGraph);
}

CommandQueue& World::GetCommandQueue()
{
	return commandQueue;
}