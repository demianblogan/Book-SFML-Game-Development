#pragma once

#include "Component.h"

namespace GUI
{
	// Container is GUI element that just contains other GUI elements.
	// You can pack them into it and select the specific one if you want.
	class Container : public Component
	{
	private:
		std::vector<Component::Pointer> children;
		int selectedChildIndex = -1;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool IsThereAnySelectedComponent() const;
		void Select(size_t index);
		void SelectNext();
		void SelectPrevious();

	public:
		using Pointer = std::shared_ptr<Container>;

		void Pack(Component::Pointer component);
		virtual bool IsSelectable() const;
		virtual void HandleEvent(const sf::Event& event) override;
	};
}