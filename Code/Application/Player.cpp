#include "Player.h"

#include "../SceneNodes/Aircraft.h"
#include "../Commands/CommandQueue.h"

// Helping functor for moving an aircraft.
struct AircraftMover
{
	sf::Vector2f velocity;

	AircraftMover(float x, float y)
		: velocity(x, y)
	{ }

	void operator()(Aircraft& aircraft, sf::Time deltaTime) const
	{
		aircraft.Accelerate(velocity);
	}
};

bool Player::IsRealTimeAction(Action action)
{
	switch (action)
	{
	case Player::Action::MoveLeft:
	case Player::Action::MoveRight:
	case Player::Action::MoveUp:
	case Player::Action::MoveDown:
		return true;

	default:
		return false;
	}
}

void Player::InitializeActions()
{
	actionBindings[Action::MoveLeft].action = GetDerivedAction<Aircraft>(AircraftMover(-moveSpeed, 0));
	actionBindings[Action::MoveRight].action = GetDerivedAction<Aircraft>(AircraftMover(+moveSpeed, 0));
	actionBindings[Action::MoveUp].action = GetDerivedAction<Aircraft>(AircraftMover(0, -moveSpeed));
	actionBindings[Action::MoveDown].action = GetDerivedAction<Aircraft>(AircraftMover(0, +moveSpeed));
}

Player::Player()
{
	keyBindings[sf::Keyboard::Left] = Action::MoveLeft;
	keyBindings[sf::Keyboard::Right] = Action::MoveRight;
	keyBindings[sf::Keyboard::Up] = Action::MoveUp;
	keyBindings[sf::Keyboard::Down] = Action::MoveDown;

	InitializeActions();

	for (auto& [action, command] : actionBindings)
	{
		command.category = (unsigned int)SceneNode::Category::PlayerAircraft;
	}
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto foundActionIter = keyBindings.find(event.key.code);
		if (foundActionIter != keyBindings.end() && !IsRealTimeAction(foundActionIter->second))
		{
			commands.Push(actionBindings[foundActionIter->second]);
		}
	}
}

void Player::HandleRealtimeInput(CommandQueue& commands)
{
	for (auto& [key, action] : keyBindings)
	{
		if (sf::Keyboard::isKeyPressed(key) && IsRealTimeAction(action))
		{
			commands.Push(actionBindings[action]);
		}
	}
}

void Player::AssignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action:
	for (auto iter = keyBindings.begin(); iter != keyBindings.end();)
	{
		if (iter->second == action)
		{
			keyBindings.erase(iter++);
		}
		else
		{
			++iter;
		}
	}

	keyBindings[key] = action;
}

sf::Keyboard::Key Player::GetAssignedKey(Action action) const
{
	for (auto& [assignedKey, currentAction] : keyBindings)
	{
		if (currentAction == action)
		{
			return assignedKey;
		}
	}

	return sf::Keyboard::Unknown;
}