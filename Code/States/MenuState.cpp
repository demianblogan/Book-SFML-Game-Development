#include "MenuState.h"

#include "../Utilities/Utilities.h"
#include "../GUI/Button.h"

MenuState::MenuState(StateStack& stack, State::Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textureHolder->Get(Textures::ID::TitleScreen);
	backgroundSprite.setTexture(texture);

	// Create "Play" button:
	auto playButton = std::make_shared<GUI::Button>(*context.fontHolder, *context.textureHolder);
	playButton->setPosition(100, 250);
	playButton->SetText("Play");
	auto playButtonCallback = [this]()
	{
		RequestStackPop();
		RequestStackPush(States::ID::Game);
	};
	playButton->SetCallback(std::move(playButtonCallback));

	// Create "Settings" button:
	auto settingsButton = std::make_shared<GUI::Button>(*context.fontHolder, *context.textureHolder);
	settingsButton->setPosition(100, 300);
	settingsButton->SetText("Settings");
	auto settingsButtonCallback = [this]()
	{
		RequestStackPop();
		RequestStackPush(States::ID::Settings);
	};
	settingsButton->SetCallback(settingsButtonCallback);

	// Create "Exit" button:
	auto exitButton = std::make_shared<GUI::Button>(*context.fontHolder, *context.textureHolder);
	exitButton->setPosition(100, 350);
	exitButton->SetText("Exit");
	auto exitButtonCallback = [this]()
	{
		RequestStackPop();
	};
	exitButton->SetCallback(exitButtonCallback);

	GUI_container.Pack(playButton);
	GUI_container.Pack(settingsButton);
	GUI_container.Pack(exitButton);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);
	window.draw(GUI_container);
}

bool MenuState::Update(sf::Time deltaTime)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	GUI_container.HandleEvent(event);
	return false;
}