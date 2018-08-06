/*
* Filename:		MenuItem.h
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#pragma once

#include <string>

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