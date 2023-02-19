#include "Application.h"

#include "../States/GameState.h"
#include "../States/MenuState.h"
#include "../States/PauseState.h"
#include "../States/TitleState.h"
#include "../Utilities/Utilities.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);
const sf::String Application::WINDOW_TITLE = "States";

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
	stateStack.RegisterState<TitleState>(States::Title);
	stateStack.RegisterState<MenuState>(States::Menu);
	stateStack.RegisterState<GameState>(States::Game);
	stateStack.RegisterState<PauseState>(States::Pause);
}

Application::Application()
	: window(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Close)
	, stateStack(State::Context(window, textureHolder, fontHolder, player))
{
	window.setKeyRepeatEnabled(false);

	fontHolder.Load(Fonts::ID::Main, fontMainPath);
	textureHolder.Load(Textures::ID::TitleScreen, textureTitleScreenPath);

	// Set statistics text settings:
	sf::Vector2f statTextPosition(5.0f, 5.0f);
	unsigned int statTextSize = 10u;
	statisticsText.setFont(fontHolder.Get(Fonts::ID::Main));
	statisticsText.setPosition(statTextPosition);
	statisticsText.setCharacterSize(statTextSize);

	// Game starts from Title Screen:
	RegisterStates();
	stateStack.PushState(States::Title);
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		// Game's delta time (time between frames) is a value of a constant "TIME_PER_FRAME".
		// So we send this value to "Update" method every frame. But to make things work properly,
		// we have to wait until game's working time has become greater than "TIME_PER_FRAME"
		// and only after that we send "TIME_PER_FRAME" value to "Update" method. 
		
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			ProcessInput();
			Update(TIME_PER_FRAME);

			if (stateStack.IsEmpty())
				window.close();
		}
		UpdateStatistics(deltaTime);
		Render();
	}
}