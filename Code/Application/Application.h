#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "../States/StateStack.h"

class Application
{
private:
	static const sf::Time ONE_FRAME_DESIRED_DURATION;
	static const sf::String WINDOW_TITLE;
	static constexpr unsigned int DEFAULT_WINDOW_HEIGHT = 480u;
	static constexpr unsigned int DEFAULT_WINDOW_WIDTH = 640u;

	sf::String fontMainPath = "Media/Fonts/Sansation.ttf";
	sf::String textureTitleScreenPath = "Media/Textures/TitleScreen.png";
	sf::String textureButtonPressedPath = "Media/Textures/ButtonPressed.png";
	sf::String textureButtonSelectedPath = "Media/Textures/ButtonSelected.png";
	sf::String textureButtonNotSelectedPath = "Media/Textures/ButtonNotSelected.png";

	sf::RenderWindow window;
	TextureHolder textureHolder;
	FontHolder fontHolder;
	Player player;
	StateStack stateStack;

	sf::Text statisticsText;
	sf::Time statisticsUpdateTime;
	std::size_t statisticsFramesCount = 0;

	void ProcessInput();
	void Update(sf::Time deltaTime);
	void UpdateStatistics(sf::Time deltaTime);
	void Render();
	void RegisterStates();

public:
	Application();

	void Run();
};