#pragma once

#include <SFML/Graphics.hpp>

namespace GUI
{
	// Base class for every GUI elements. Every GUI element must be drawable, transformable
	// selectable and activable. Also every GUI element can handle input event by itself.
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	private:
		bool isSelected = false;
		bool isActive = false;

	public:
		using Pointer = std::shared_ptr<Component>;

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