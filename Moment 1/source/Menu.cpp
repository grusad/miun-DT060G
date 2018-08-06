/*
* Filename:		Menu.cpp
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#include "Menu.h"
#include "Input.h"
#include <iomanip>
#include <iostream>

//Prints the menus items.
void Menu::print() const {

	for (int i = 1; i <= items.size(); i++) {
		MenuItem item = items[i - 1];
		std::cout << i << ". " << std::left << std::setw(24) << item.getText();
		if (!item.isEnabled()) std::cout << "[Unavalible]";	//If a menuitem is unavalible
		std::cout << std::endl;
	}
}

// Retreives an integer as an alternative 
int Menu::getAlternative() {

	while (true) {

		int value = Input::getInteger(1, items.size());
		if (getItem(value - 1).isEnabled()) return value;	// If chosen alternative is avalible...
		else std::cout << "Unavalible..." << std::endl;		
	}

}
// Sets all items to be avalible
void Menu::enableAll() {
	for (MenuItem &item : items) {
		item.setEnabled(true);
	}
}