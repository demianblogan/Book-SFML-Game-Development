#include "PauseState.h"

#include "../Utilities/Utilities.h"

PauseState::PauseState(StateStack& stack, State::Context context)
	: State(stack, context)
{
	sf::Font& font = context.fontHolder->Get(Fonts::ID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	// Adjust the pause title text's settings:
	pauseTitleText.setFont(font);
	pauseTitleText.setString("Game paused");
	pauseTitleText.setCharacterSize(70);
	CenterSFMLAssetOrigin(pauseTitleText);
	pauseTitleText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	// Adjust the instruction text's settings:
	instructionText.setFont(font);
	instructionText.setString("(Press Backspace to return to the main menu");
	CenterSFMLAssetOrigin(instructionText);
	instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	// Background shape will just a half transparent picture.
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseTitleText);
	window.draw(instructionText);
}

bool PauseState::Update(sf::Time deltaTime)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		RequestStackPop();
	}

	if (event.key.code == sf::Keyboard::BackSpace)
	{
		RequestStateClear();
		RequestStackPush(States::Menu);
	}

	return false;
}