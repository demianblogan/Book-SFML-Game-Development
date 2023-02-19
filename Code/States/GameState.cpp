#include "GameState.h"

#include "../Application/Player.h"

GameState::GameState(StateStack& stack, State::Context context)
	: State(stack, context)
	, world(*context.window)
	, player(*context.player)
{ }

void GameState::Draw()
{
	world.Draw();
}

bool GameState::Update(sf::Time deltaTime)
{
	world.Update(deltaTime);

	CommandQueue& commands = world.GetCommandQueue();
	player.HandleRealtimeInput(commands);

	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.GetCommandQueue();
	player.HandleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		RequestStackPush(States::ID::Pause);

	return true;
}