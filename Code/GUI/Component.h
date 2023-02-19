#pragma once

#include <SFML/Graphics.hpp>

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	private:
		bool isSelected = false;
		bool isActive = false;

	public:
		using Pointer = std::shared_ptr<Component>;

		Component() = default;
		virtual ~Component();

		virtual bool IsSelectable() const = 0;
		bool IsSelected() const;
		virtual void Select();
		virtual void Deselect();

		virtual bool IsActive() const;
		virtual void Activate();
		virtual void Deactivate();
		virtual void HandleEvent(const sf::Event& event) = 0;
	};
}