#include "State.h"

#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, Player& player)
	: window(&window)
	, textureHolder(&textureHolder)
	, fontHolder(&fontHolder)
	, player(&player)
{ }

void State::RequestStackPush(States::ID stateID)
{
	stack->PushState(stateID);
}

void State::RequestStackPop()
{
	stack->PopState();
}

void State::RequestStateClear()
{
	stack->ClearStates();
}

State::Context State::GetContext() const
{
	return context;
}

State::State(StateStack& stack, Context context)
	: stack(&stack)
	, context(context)
{ }

State::~State()
{ }