#include "Application.h"

#include "../States/GameState.h"
#include "../States/MenuState.h"
#include "../States/PauseState.h"
#include "../States/SettingsState.h"
#include "../States/TitleState.h"
#include "../Utilities/Utilities.h"

const sf::Time Application::ONE_FRAME_DESIRED_DURATION = sf::seconds(1.0f / 60.0f);
const sf::String Application::WINDOW_TITLE = "Menus";

void Application::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.HandleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Application::Update(sf::Time deltaTime)
{
	stateStack.Update(deltaTime);
}

void Application::UpdateStatistics(sf::Time deltaTime)
{
	// We want the FPS counter to show every second. So we have our own
	// clock "statisticsUpdateTime" that holds value of how much time has passed
	// since the application lunch. To increment it every frame, we add delta time
	// to it and check if it's greater than 1 second. If is - we change the 
	// representation string by updating the number of FPS.

	statisticsUpdateTime += deltaTime;
	statisticsFramesCount++;
	if (statisticsUpdateTime >= sf::seconds(1.0f))
	{
		statisticsText.setString("FPS: " + std::to_string(statisticsFramesCount));

		statisticsUpdateTime -= sf::seconds(1.0f);
		statisticsFramesCount = 0;
	}
}

void Application::Render()
{
	window.clear();

	stateStack.Draw();
	window.setView(window.getDefaultView());
	window.draw(statisticsText);

	window.display();
}

void Application::RegisterStates()
{
	stateStack.RegisterState<TitleState>(States::ID::Title);
	stateStack.RegisterState<MenuState>(States::ID::Menu);
	stateStack.RegisterState<GameState>(States::ID::Game);
	stateStack.RegisterState<PauseState>(States::ID::Pause);
	stateStack.RegisterState<SettingsState>(States::ID::Settings);
}

Application::Application()
	: window(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close)
	, stateStack(State::Context(window, textureHolder, fontHolder, player))
{
	window.setKeyRepeatEnabled(false);

	// Load resources:
	fontHolder.Load(Fonts::ID::Main, fontMainPath);
	textureHolder.Load(Textures::ID::TitleScreen, textureTitleScreenPath);
	textureHolder.Load(Textures::ID::ButtonNotSelected, textureButtonNotSelectedPath);
	textureHolder.Load(Textures::ID::ButtonSelected, textureButtonSelectedPath);
	textureHolder.Load(Textures::ID::ButtonPressed, textureButtonPressedPath);

	// Set statistics text settings:
	statisticsText.setFont(fontHolder.Get(Fonts::ID::Main));
	statisticsText.setPosition(5.0f, 5.0f);
	statisticsText.setCharacterSize(10u);

	// Game starts from Title Screen:
	RegisterStates();
	stateStack.PushState(States::ID::Title);
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		// Game's delta time (time between frames) is a value of a constant "ONE_FRAME_DESIRED_DURATION".
		// So we send this value to "Update" method every frame. But to make things work properly,
		// we have to wait until game's working time has become greater than "ONE_FRAME_DESIRED_DURATION"
		// and only after that we send "ONE_FRAME_DESIRED_DURATION" value to "Update" method. 
		
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		while (timeSinceLastUpdate > ONE_FRAME_DESIRED_DURATION)
		{
			timeSinceLastUpdate -= ONE_FRAME_DESIRED_DURATION;

			ProcessInput();
			Update(ONE_FRAME_DESIRED_DURATION);

			if (stateStack.IsEmpty())
				window.close();
		}
		UpdateStatistics(deltaTime);
		Render();
	}
}