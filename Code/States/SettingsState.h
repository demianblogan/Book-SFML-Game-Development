#pragma once

#include <array>
#include "../Application/Player.h"
#include "State.h"
#include "../GUI/Button.h"
#include "../GUI/Container.h"
#include "../GUI/Label.h"

class SettingsState : public State
{
private:
	sf::Sprite backgroundSprite;
	GUI::Container GUI_container;
	std::array<GUI::Button::Pointer, (size_t)Player::Action::ActionCount> bindingButtons;
	std::array<GUI::Label::Pointer, (size_t)Player::Action::ActionCount> bindingLabels;

	void UpdateLabels();
	void AddButtonLabel(Player::Action action, float y, const std::string& text, Context context);

public:
	SettingsState(StateStack& stack, Context context);

	virtual bool HandleEvent(const sf::Event& event) override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual void Draw() override;
};