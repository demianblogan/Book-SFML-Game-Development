#pragma once

#include <map>
#include <SFML/Window.hpp>
#include "../Commands/Command.h"

class CommandQueue;

// Player is a class that contains all contol input things related to the player:
// keys that player can press, actions that will be produced after hitting particular key,
// and game commands that will be executed by actions.
class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

private:
	std::map<sf::Keyboard::Key, Action> keyBindings;
	std::map<Action, Command> actionBindings;

	float moveSpeed = 200.0f;

	static bool IsRealTimeAction(Action action);
	void InitializeActions();

public:
	Player();

	void HandleEvent(const sf::Event& event, CommandQueue& commands);
	void HandleRealtimeInput(CommandQueue& commands);

	void AssignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key GetAssignedKey(Action action) const;
};