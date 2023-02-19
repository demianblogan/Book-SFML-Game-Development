#include "MenuState.h"

#include "../Utilities/Utilities.h"

MenuState::MenuState(StateStack& stack, State::Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textureHolder->Get(Textures::ID::TitleScreen);
	sf::Font& font = context.fontHolder->Get(Fonts::ID::Main);

	backgroundSprite.setTexture(texture);

	// Create an option "Play" and add it to the options:
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	CenterSFMLAssetOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.0f);
	options.push_back(playOption);

	// Create an option "Exit" and add it to the options:
	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	CenterSFMLAssetOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0, 30));
	options.push_back(exitOption);

	UpdateOptionText();
}

void MenuState::UpdateOptionText()
{
	if (options.empty())
	{
		return;
	}

	for (sf::Text& text : options)
	{
		text.setFillColor(sf::Color::White);
	}

	options[optionIndex].setFillColor(sf::Color::Red);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);

	for (const sf::Text& text : options)
	{
		window.draw(text);
	}
}

bool MenuState::Update(sf::Time deltaTime)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (optionIndex == (size_t)OptionMame::Play)
		{
			RequestStackPop();
			RequestStackPush(States::Game);
		}
		else if (optionIndex == (size_t)OptionMame::Exit)
		{
			RequestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		if (optionIndex > 0)
		{
			optionIndex--;
		}
		else
		{
			optionIndex = options.size() - 1;
		}

		UpdateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (optionIndex < options.size() - 1)
		{
			optionIndex++;
		}
		else
		{
			optionIndex = 0;
		}

		UpdateOptionText();
	}

	return true;
}