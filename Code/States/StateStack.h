#pragma once

#include <functional>
#include <map>
#include <vector>
#include "State.h"

// The concept of handling states in the game is next:
// After starting the application you will be in TitleState.
// You can switch between TitleState and MenuState. The same
// for MenuState and GameState. But sometimes there might be
// two states in one time. For example when you are in GameState
// and want to pause it - you call PauseState and it will be on
// "top" of Game State. So that's why in concept of handling states
// you see a word "Stack".
// If you want to change the game state, you should next:
// - pop current state from the stack;
// - push new state to the stack;
// If you want to add new state ABOVE current state, you should next:
// - push new state to the stack;
// If you want to close the game by closing all states, you should next:
// - clear the stack;
class StateStack : private sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

private:
	// Every state follows next algorythm:
	// 1. Handle input
	// 2. Update it
	// 3. Render it
	// And because every state is connected to the state stack, it can calls
	// the stack's method whenever it wants. However, in the middle of handling input
	// or update iteration by the stack, it is not possible to alter the active state
	// stack because it would generate a conflict when adding/removing objects to a
	// container that is being iterated. Because of this, those functions don't 
	// immediately push or pop states into the stack, but rather register these actions 
	// in a pending action list, so they can be processed later, when it's safe. That's
	// why we created PendingChange strucutre.
	struct PendingChange
	{
		Action action;
		States::ID stateID;

		explicit PendingChange(Action action, States::ID stateID = States::None);
	};

	// We want to use stack's mechanism but std::stack has many restrictions. That's why
	// we chose std::vector and we will handle it as a stack.
	std::vector<State::Pointer> stack;
	std::vector<PendingChange> pendingList;
	State::Context context;
	std::map<States::ID, std::function<State::Pointer()>> stateCreatingFactories;

	State::Pointer CreateState(States::ID stateID);
	void ApplyPendingChanges();

public:
	explicit StateStack(State::Context context);

	template <typename T>
	void RegisterState(States::ID stateID);

	void Update(sf::Time deltaTime);
	void Draw();
	void HandleEvent(const sf::Event& event);

	void PushState(States::ID stateID);
	void PopState();
	void ClearStates();
	bool IsEmpty() const;
};

template <typename T>
void StateStack::RegisterState(States::ID stateID)
{
	stateCreatingFactories[stateID] = [this]()
	{
		return State::Pointer(new T(*this, context));
	};
}