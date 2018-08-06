/*
* Filename:		MenuItem.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef JUKEBOX_MENUITEM_H
#define JUKEBOX_MENUITEM_H

#include <functional>
#include <string>

// a class represents an item for the menu class
class MenuItem
{
public:
	using Func = std::function<void()>;

	MenuItem() = default;
	MenuItem(std::string in_name, Func in_callback);
	~MenuItem();

	//executes the callback function
	void Exec();
	std::string GetName() const;
	void SetState(bool active);

private:
	std::string name;
	bool isActive = true;

	//we store the function passed to the constructor here
	Func callback;
};


#endif //JUKEBOX_MENUITEM_H

