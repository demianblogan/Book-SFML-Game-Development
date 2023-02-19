#pragma once

#include "State.h"
#include "../Application/World.h"

class Player;
class StateStack;

// GameState is a class that represents actually that game state, where
// user can play (the main part of a game).
class GameState : public State
{
private:
	World world;
	Player& player;

public:
	GameState(StateStack& stack, State::Context context);

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};