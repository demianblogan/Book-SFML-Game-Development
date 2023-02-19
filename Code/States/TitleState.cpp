#include "TitleState.h"

#include "../Utilities/Utilities.h"

TitleState::TitleState(StateStack& stack, State::Context context)
	: State(stack, context)
	, textAppereanceTime(sf::Time::Zero)
{
	backgroundSprite.setTexture(context.textureHolder->Get(Textures::ID::TitleScreen));

	// Adjust title text settings:
	text.setFont(context.fontHolder->Get(Fonts::ID::Main));
	text.setString("Press any key to start");
	CenterSFMLAssetOrigin(text);
	text.setPosition(context.window->getView().getSize() / 2.0f);
}

void TitleState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.draw(backgroundSprite);

	if (isTextNeedToBeShown)
		window.draw(text);
}

bool TitleState::Update(sf::Time deltaTime)
{
	// Title text has simple blinking animation. Every half of a second
	// it appears and desappears.
	textAppereanceTime += deltaTime;
	if (textAppereanceTime >= sf::seconds(0.5f))
	{
		isTextNeedToBeShown = !isTextNeedToBeShown;
		textAppereanceTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		RequestStackPop();
		RequestStackPush(States::ID::Menu);
	}

	return true;
}