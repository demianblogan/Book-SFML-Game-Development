#pragma once

#include "Component.h"
#include "../Application/ResourceHolder.h"

namespace GUI
{
	class Label : public Component
	{
	private:
		sf::Text text;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		using Pointer = std::shared_ptr<Label>;

		Label(const std::string& text, const FontHolder& fontHolder);
	
		virtual bool IsSelectable() const override;
		void SetText(const std::string& text);
		virtual void HandleEvent(const sf::Event& event) override;
	};
}