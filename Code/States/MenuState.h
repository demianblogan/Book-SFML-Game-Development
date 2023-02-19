#pragma once

#include "State.h"

// MenuState is a class that contains all things related to
// the menu of the game. Game has only one menu for now.
class MenuState : public State
{
private:
	enum class OptionMame
	{
		Play,
		Exit
	};

	sf::Sprite backgroundSprite;
	std::vector<sf::Text> options;
	size_t optionIndex = 0;

public:
	MenuState(StateStack& stack, State::Context context);

	void UpdateOptionText();

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};