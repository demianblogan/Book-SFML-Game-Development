#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Application/ResourceHolder.h"

class StateStack;
class Player;

namespace States
{
	enum ID
	{
		None,
		Title,
		Menu,
		Game,
		Loading,
		Pause
	};
}

// Game is divided by states. You can consider the concept of a state as
// a game scene, for example title screen scene, menu scene, game scene, loading
// scene, pause scene. Whey are in some of them - you are in a specific game state.
// State is a class that contains everything about managing resources on current
// scene (textures, fonts, player) and manipulate them. It's just a base class
// for specific game states. You can find MenuState, GameState and other classes,
// which have specific behaviour.
class State
{
public:
	using Pointer = std::unique_ptr<State>;

	// When create a state, it has to be connected to most important and fundamental
	// things in the game: window, resources and player. So this structure contains
	// all of it and it will be easier, if you can use them in every state without
	// dupicating these objects. That's why this structure contains only pointers.
	struct Context
	{
		sf::RenderWindow* window;
		TextureHolder* textureHolder;
		FontHolder* fontHolder;
		Player* player;

		Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, Player& player);
	};

private:
	StateStack* stack;
	Context context;

protected:
	void RequestStackPush(States::ID stateID);
	void RequestStackPop();
	void RequestStateClear();

	Context GetContext() const;

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void Draw() = 0;
	virtual bool Update(sf::Time deltaTime) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;
};