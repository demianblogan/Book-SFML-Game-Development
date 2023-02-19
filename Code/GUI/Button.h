#pragma once

#include <functional>
#include "Component.h"
#include "../Application/ResourceHolder.h"

namespace GUI
{
	// Label is a class that represents GUI element Button. It has background sprite,
	// foreground text, and callback function to call when clicking on it.
	class Button : public Component
	{
	public:
		using Pointer = std::shared_ptr<Button>;
		using Callback = std::function<void()>;

	private:
		Callback callback;
		const sf::Texture& buttonNotSelectedTexture;
		const sf::Texture& buttonSelectedTexture;
		const sf::Texture& buttonPressedTexture;
		sf::Sprite sprite;
		sf::Text text;
		bool isToggle = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		Button(const FontHolder& fontHolder, const TextureHolder& textureHolder);

		void SetCallback(Callback callback);
		void SetText(const std::string& text);
		void SetToggle(bool flag);

		virtual bool IsSelectable() const override;
		virtual void Select() override;
		virtual void Deselect() override;

		virtual void Activate() override;
		virtual void Deactivate() override;

		virtual void HandleEvent(const sf::Event& event) override;
	};
}