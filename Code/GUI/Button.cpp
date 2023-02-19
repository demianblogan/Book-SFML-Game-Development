#include "Button.h"

#include "../Utilities/Utilities.h"

namespace GUI
{
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite, states);
		target.draw(text, states);
	}

	Button::Button(const FontHolder& fontHolder, const TextureHolder& textureHolder)
		: buttonNotSelectedTexture(textureHolder.Get(Textures::ID::ButtonNotSelected))
		, buttonSelectedTexture(textureHolder.Get(Textures::ID::ButtonSelected))
		, buttonPressedTexture(textureHolder.Get(Textures::ID::ButtonPressed))
		, text("", fontHolder.Get(Fonts::ID::Main), 16u)
	{
		sprite.setTexture(buttonNotSelectedTexture);

		sf::FloatRect bounds = sprite.getLocalBounds();
		text.setPosition(bounds.width / 2.0f, bounds.height / 2.0f);
	}


	void Button::SetCallback(Callback callback)
	{
		this->callback = std::move(callback);
	}

	void Button::SetText(const std::string& text)
	{
		this->text.setString(text);
		CenterSFMLAssetOrigin(this->text);
	}

	void Button::SetToggle(bool flag)
	{
		isToggle = flag;
	}


	bool Button::IsSelectable() const
	{
		return true;
	}

	void Button::Select()
	{
		Component::Select();

		sprite.setTexture(buttonSelectedTexture);
	}

	void Button::Deselect()
	{
		Component::Deselect();

		sprite.setTexture(buttonNotSelectedTexture);
	}


	void Button::Activate()
	{
		Component::Activate();

		// If we are toggle then we should show that the button is pressed and thus "toggled".
		if (isToggle)
		{
			sprite.setTexture(buttonPressedTexture);
		}

		if (callback != nullptr)
		{
			callback();
		}

		// If we are not a toggle then deactivate the button since we are just momentarily activated.
		if (!isToggle)
		{
			Deactivate();
		}
	}

	void Button::Deactivate()
	{
		Component::Deactivate();

		if (isToggle)
		{
			sprite.setTexture(IsSelected() ? buttonSelectedTexture : buttonNotSelectedTexture);
		}
	}


	void Button::HandleEvent(const sf::Event& event)
	{ }
}