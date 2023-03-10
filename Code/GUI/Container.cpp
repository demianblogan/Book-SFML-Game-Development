#include "Container.h"

namespace GUI
{
	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (const Component::Pointer& child : children)
		{
			target.draw(*child, states);
		}
	}

	bool Container::IsThereAnySelectedComponent() const
	{
		return selectedChildIndex >= 0;
	}

	void Container::Select(size_t index)
	{
		if (children[index]->IsSelectable())
		{
			if (IsThereAnySelectedComponent())
			{
				children[selectedChildIndex]->Deselect();
			}

			children[index]->Select();
			selectedChildIndex = index;
		}
	}

	void Container::SelectNext()
	{
		if (!IsThereAnySelectedComponent())
		{
			return;
		}

		// Search next component that is selectable:
		int nextIndex = selectedChildIndex;
		do
		{
			nextIndex = (nextIndex + 1) % (int)children.size();

		} while (!children[nextIndex]->IsSelectable());

		Select(nextIndex);
	}

	void Container::SelectPrevious()
	{
		if (!IsThereAnySelectedComponent())
		{
			return;
		}

		// Search previous component that is selectable:
		int previousIndex = selectedChildIndex;
		do
		{
			previousIndex = (previousIndex + children.size() - 1) % children.size();

		} while (!children[previousIndex]->IsSelectable());

		Select(previousIndex);
	}

	void Container::Pack(Component::Pointer component)
	{
		children.push_back(component);

		if (!IsThereAnySelectedComponent() && component->IsSelectable())
		{
			Select(children.size() - 1);
		}
	}

	bool Container::IsSelectable() const
	{
		// Container cannot be selectable.
		return false;
	}

	void Container::HandleEvent(const sf::Event& event)
	{
		if (IsThereAnySelectedComponent() && children[selectedChildIndex]->IsActive())
		{
			children[selectedChildIndex]->HandleEvent(event);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				SelectPrevious();
			}
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				SelectNext();
			}
			else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (IsThereAnySelectedComponent())
				{
					children[selectedChildIndex]->Activate();
				}
			}
		}
	}
}