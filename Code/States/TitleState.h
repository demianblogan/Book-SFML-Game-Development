#pragma once

#include "State.h"

// TitleState is a class that represents the beginning scene of the application.
// You can consider is as a start screen or intro of the game.
class TitleState : public State
{
private:
	sf::Sprite backgroundSprite;
	sf::Text text;
	sf::Time textAppereanceTime;
	bool isTextNeedToBeShown = true;

public:
	TitleState(StateStack& stack, State::Context context);

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};