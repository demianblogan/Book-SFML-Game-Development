#pragma once

#include <queue>
#include "Command.h"

// CommandQueue is a wrapping class for a queue of commands.
// It restricts the std::queue methods and gives only needed ones.
class CommandQueue
{
private:
	std::queue<Command> queue;

public:
	void Push(const Command& command);
	Command Pop();
	bool IsEmpty() const;
};