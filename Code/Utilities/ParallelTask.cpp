#include "ParallelTask.h"

void ParallelTask::RunTask()
{
	// Now the task of of class is hardcoded and you can't send your function
	// to it. The test task is simple - just wait for 10 seconds.

	float waitingTimeInSec = 10.0f;
	bool taskIsEnded = false;
	while (!taskIsEnded)
	{
		sf::Lock lock(mutex);
		if (elapsedTime.getElapsedTime().asSeconds() >= waitingTimeInSec)
		{
			taskIsEnded = true;
		}
	}

	{
		sf::Lock lock(mutex);
		isFinished = true;
	}
}

ParallelTask::ParallelTask()
	: thread(&ParallelTask::RunTask, this)
{ }

void ParallelTask::Execute()
{
	isFinished = false;
	elapsedTime.restart();
	thread.launch();
}

bool ParallelTask::IsFinished()
{
	sf::Lock lock(mutex);
	return isFinished;
}

float ParallelTask::GetCompletion()
{
	sf::Lock lock(mutex);

	// Function that is being executed for now is just a dummy (see ParallelTask::RunTask code).
	// It just waits for 10 seconds and finished. So to calculate its completion, we need to
	// divide the elapsed time of its execution by 10 seconds. That will give us a number from
	// 0 to 1 that is the completion percentage.
	return elapsedTime.getElapsedTime().asSeconds() / 10;
}