/*
* Filename:		Menu.h
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#pragma once

#include <vector>
#include "MenuItem.h"


class Menu {

private:
	std::vector<MenuItem> items;

public:
	void add(const MenuItem item) { items.push_back(item); };
	int getSize() const { return items.size(); };
	MenuItem getItem(int index) const { return items[index]; };
	void print() const;
	int getAlternative(); 
	void enableAll();

};