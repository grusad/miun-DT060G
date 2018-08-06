/*
* Filename:		MenuItem.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "MenuItem.h"


//Create a menuitem giving it a name and a function to execute
MenuItem::MenuItem(std::string in_name, Func in_callback) : name(in_name), callback(in_callback)
{
}

MenuItem::~MenuItem()
{
}

void MenuItem::Exec()
{
	if (isActive)
	{
		callback();
	}
}

std::string MenuItem::GetName() const
{
	if (isActive)
	{
		return name;
	}

	return name + " INACTIVE";
}

void MenuItem::SetState(bool active)
{
	isActive = active;
}
