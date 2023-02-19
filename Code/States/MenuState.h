#pragma once

#include "State.h"
#include "../GUI/Container.h"

// MenuState is a class that contains all things related to
// the menu of the game. Game has only one menu for now.
class MenuState : public State
{
private:
	sf::Sprite backgroundSprite;
	GUI::Container GUI_container;

public:
	MenuState(StateStack& stack, State::Context context);

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};