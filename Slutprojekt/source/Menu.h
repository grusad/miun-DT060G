/*
* Filename:		Menu.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef JUKEBOX_MENU_H
#define JUKEBOX_MENU_H

#include "MenuItem.h"
#include <string>
#include <map>

// a class represents a menu
class Menu
{
public:
	Menu() = default;
	Menu(std::string name) : name(std::move(name)) {}
	~Menu() = default;

	void ShowSub();
	void ShowMain();

	void AddItem(MenuItem item, int index);

	//set item with with corresponding id to active/inactive
	void SetItemState(int id, bool active);
	static void ClearScreen();


private:
	std::map<int, MenuItem> items;
	std::string name;
};


#endif //JUKEBOX_MENU_H