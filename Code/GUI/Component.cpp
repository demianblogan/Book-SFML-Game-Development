#include "Component.h"

namespace GUI
{
	Component::~Component()
	{ }

	bool Component::IsSelected() const
	{
		return isSelected;
	}

	void Component::Select()
	{
		isSelected = true;
	}

	void Component::Deselect()
	{
		isSelected = false;
	}


	bool Component::IsActive() const
	{
		return isActive;
	}

	void Component::Activate()
	{
		isActive = true;
	}

	void Component::Deactivate()
	{
		isActive = false;
	}
}