#include "SettingsState.h"

#include "../Utilities/Utilities.h"

void SettingsState::UpdateLabels()
{
	Player& player = *GetContext().player;

	for (size_t i = 0; i < (size_t)Player::Action::ActionCount; i++)
	{
		sf::Keyboard::Key key = player.GetAssignedKey((Player::Action)i);
		bindingLabels[i]->SetText(ConvertToString(key));
	}
}

void SettingsState::AddButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
	size_t actionIndex = (size_t)action;

	// Create button binding:
	bindingButtons[actionIndex] = std::make_shared<GUI::Button>(*context.fontHolder, *context.textureHolder);
	bindingButtons[actionIndex]->setPosition(80.0f, y);
	bindingButtons[actionIndex]->SetText(text);
	bindingButtons[actionIndex]->SetToggle(true);

	// Create label binding:
	bindingLabels[actionIndex] = std::make_shared<GUI::Label>("", *context.fontHolder);
	bindingLabels[actionIndex]->setPosition(300.0f, y + 15.0f);

	// Pack the button and label:
	GUI_container.Pack(bindingButtons[actionIndex]);
	GUI_container.Pack(bindingLabels[actionIndex]);
}

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
{
	backgroundSprite.setTexture(context.textureHolder->Get(Textures::ID::TitleScreen));

	// Build key binding buttons and labels:
	AddButtonLabel(Player::Action::MoveLeft, 150.0f, "Move Left", context);
	AddButtonLabel(Player::Action::MoveRight, 200.0f, "Move Right", context);
	AddButtonLabel(Player::Action::MoveUp, 250.0f, "Move Up", context);
	AddButtonLabel(Player::Action::MoveDown, 300.0f, "Move Down", context);

	UpdateLabels();

	// Create "Back" button:
	auto backButton = std::make_shared<GUI::Button>(*context.fontHolder, *context.textureHolder);
	backButton->setPosition(80.0f, 375.0f);
	backButton->SetText("Back");
	backButton->SetCallback(std::bind(&SettingsState::RequestStackPop, this));
	
	GUI_container.Pack(backButton);
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key:
	for (size_t i = 0; i < (size_t)Player::Action::ActionCount; i++)
	{
		if (bindingButtons[i]->IsActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				GetContext().player->AssignKey((Player::Action)i, event.key.code);
				bindingButtons[i]->Deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container:
	if (isKeyBinding)
	{
		UpdateLabels();
	}
	else
	{
		GUI_container.HandleEvent(event);
	}

	return false;
}

bool SettingsState::Update(sf::Time deltaTime)
{
	return true;
}

void SettingsState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;

	window.draw(backgroundSprite);
	window.draw(GUI_container);
}