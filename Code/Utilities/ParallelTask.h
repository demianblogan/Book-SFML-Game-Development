#pragma once

#include <SFML/System.hpp>

// ParallelTask is a class that can execute a function
// in a parallel thread. By now it doesn't do anything
// due to no need for this.
class ParallelTask
{
private:
	sf::Thread thread;
	sf::Clock elapsedTime;
	sf::Mutex mutex;
	bool isFinished = false;

	void RunTask();

public:
	ParallelTask();

	void Execute();
	bool IsFinished();
	float GetCompletion();
};