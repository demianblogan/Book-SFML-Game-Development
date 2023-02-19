#pragma once

#include "Component.h"

namespace GUI
{
	class Container : public Component
	{
	private:
		std::vector<Component::Pointer> children;
		int selectedChildIndex = -1;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		bool HasSelection() const;
		void Select(size_t index);
		void SelectNext();
		void SelectPrevious();

	public:
		using Pointer = std::shared_ptr<Container>;

		Container() = default;

		void Pack(Component::Pointer component);
		virtual bool IsSelectable() const;
		virtual void HandleEvent(const sf::Event& event) override;
	};
}