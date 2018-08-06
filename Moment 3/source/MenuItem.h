/*
* Filename:		MenuItem.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once

#include <string>

// Represents an item for the menu.
class MenuItem
{
private:

	std::string m_menuText;
	bool m_enabled;

public:

	MenuItem(std::string menuText, bool enabled) : m_menuText(menuText), m_enabled(enabled) {};

	std::string getText() const { return m_menuText; };
	bool isEnabled() const { return m_enabled; };
	void setEnabled(const bool enabled) { m_enabled = enabled; };

};