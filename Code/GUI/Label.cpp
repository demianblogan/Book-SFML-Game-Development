#include "Label.h"

namespace GUI
{

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(text, states);
	}

	Label::Label(const std::string& text, const FontHolder& fontHolder)
		: text(text, fontHolder.Get(Fonts::ID::Main), 16u)
	{ }

	bool Label::IsSelectable() const
	{
		// Label cannot be selectable.
		return false;
	}

	void Label::SetText(const std::string& text)
	{
		this->text.setString(text);
	}

	void Label::HandleEvent(const sf::Event& event)
	{ }
}