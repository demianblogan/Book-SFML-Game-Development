#pragma once

#include "State.h"

// PauseState is a class that represent pause menu while GameState
// is running. It contains simple elements as background, pause text,
// and instructions of what to do.
class PauseState : public State
{
private:
	sf::Text pauseTitleText;
	sf::Text instructionText;

public:
	PauseState(StateStack& stack, State::Context context);

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};