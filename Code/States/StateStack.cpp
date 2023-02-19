#include "StateStack.h"

#include <assert.h>

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action), stateID(stateID)
{ }

StateStack::StateStack(State::Context context)
	: context(context)
{ }

State::Pointer StateStack::CreateState(States::ID stateID)
{
	auto found = stateCreatingFactories.find(stateID);
	assert(found != stateCreatingFactories.end());

	return found->second();
}

void StateStack::ApplyPendingChanges()
{
	for (PendingChange change : pendingList)
	{
		switch (change.action)
		{
		case Action::Push:
			stack.push_back(CreateState(change.stateID));
			break;

		case Action::Pop:
			stack.pop_back();
			break;

		case Action::Clear:
			stack.clear();
			break;
		}
	}

	pendingList.clear();
}

void StateStack::Update(sf::Time deltaTime)
{
	// Iterate form top to bottom, stop as soon as Update() returns false:
	for (auto iterator = stack.rbegin(); iterator != stack.rend(); ++iterator)
	{
		if (!(*iterator)->Update(deltaTime))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateStack::Draw()
{
	// Draw all active states from bottom to top:
	for (State::Pointer& state : stack)
	{
		state->Draw();
	}
}

void StateStack::HandleEvent(const sf::Event& event)
{
	// Iterate form top to bottom, stop as soon as HandleEvent() returns false:
	for (auto iterator = stack.rbegin(); iterator != stack.rend(); ++iterator)
	{
		if (!(*iterator)->HandleEvent(event))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateID)
{
	pendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::PopState()
{
	pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates()
{
	pendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::IsEmpty() const
{
	return stack.empty();
}