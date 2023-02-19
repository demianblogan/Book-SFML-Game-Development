#include "LoadingState.h"

#include "../Utilities/Utilities.h"

LoadingState::LoadingState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::RenderWindow& window = *GetContext().window;
	sf::Font& font = context.fontHolder->Get(Fonts::ID::Main);
	sf::Vector2f viewSize = window.getView().getSize();

	// Adjust the loading text:
	loadingText.setFont(font);
	loadingText.setString("Loading Resources");
	CenterSFMLAssetOrigin(loadingText);
	loadingText.setPosition(viewSize.x / 2, viewSize.y / 2 + 50);

	// Adjust the progress bar's background:
	progressBarBackground.setFillColor(sf::Color::White);
	progressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
	progressBarBackground.setPosition(10, loadingText.getPosition().y + 40);

	// Adjust the progress bar:
	progressBar.setFillColor(sf::Color(100, 100, 100));
	progressBar.setSize(sf::Vector2f(200, 10));
	progressBar.setPosition(10, loadingText.getPosition().y + 40);

	SetCompletion(0);

	loadingTask.Execute(); // this code doesn't do anything for now.
}

void LoadingState::SetCompletion(float percentage)
{
	if (percentage > 1)
	{
		percentage = 1;
	}

	// Wide the progress bar depending on the completion percentage:
	progressBar.setSize(sf::Vector2(progressBarBackground.getSize().x * percentage, progressBarBackground.getSize().y));
}

void LoadingState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	window.setView(window.getDefaultView());
	window.draw(loadingText);
	window.draw(progressBarBackground);
	window.draw(progressBar);
}

bool LoadingState::Update(sf::Time deltaTime)
{
	if (loadingTask.IsFinished())
	{
		RequestStackPop();
		RequestStackPush(States::ID::Game);
	}
	else
	{
		SetCompletion(loadingTask.GetCompletion());
	}

	return true;
}

bool LoadingState::HandleEvent(const sf::Event& event)
{
	return true;
}