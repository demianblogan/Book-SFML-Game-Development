#pragma once

#include "State.h"
#include "../Utilities/ParallelTask.h"

// LoadingState is a class that contains loading screen things:
// loading text and progress bar.
class LoadingState : public State
{
private:
	sf::Text loadingText;
	sf::RectangleShape progressBarBackground;
	sf::RectangleShape progressBar;
	
	ParallelTask loadingTask;

public:
	LoadingState(StateStack& stack, Context context);

	/// <param name="percentage">From 0 to 1 (i.e. 0.34 = 34%)</param>
	void SetCompletion(float percentage);

	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};