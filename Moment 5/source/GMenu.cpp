#ifdef _WIN32
#include <conio.h>
#endif

#include "GMenu.h"
#include <iostream>
#include <iomanip>
#include "Input.h"

GMenu::GMenu(const std::string title) {
	this->title = title;
	this->currentSelected = 0;
	this->running = true;
}

GMenu::GMenu() {
	this->title = "";
	this->running = true;
}

void GMenu::addItem(GItem item) {
	items.push_back(item);
}

void GMenu::setTitle(const std::string title) {
	this->title = title;
}

void GMenu::showAndListen() {

	while (running) {

		clearScreen();

		std::cout << "****  " << title << " ****" << std::endl << std::endl;

		for (int i = 0; i < items.size(); i++) {

			if (i == currentSelected) {
				std::cout << "> ";
			}

			std::cout << std::left << std::setw(24) << items[i].getText();

			if (items[i].isLocked()) {
				std::cout << "[LOCKED]";
			}

			std::cout << std::endl;

		}

		std::cout << std::endl << std::endl;

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

		std::cout << "[A + ENTER] = up, [D + ENTER] = down, [S + ENTER] = select, [Q + ENTER] = quit" << std::endl;

		char input;
		std::cin >> input;
		std::cin.get();

		if (input == 'd' || input == 'D') {
			nextItem();
		}
		else if (input == 'a' || input == 'A') {
			prevItem();
		}
		else if (input == 's' || input == 'S') {
			execItem();
		}
		else if (input == 'q' || input == 'Q') {
			terminate();
		}

	
#elif _WIN32

#define KEY_UP		72
#define KEY_DOWN	80
#define ENTER		13
#define ESC			27

		std::cout << "[UP] = up, [DOWN] = down, [ENTER] = select, [ESC] = exit" << std::endl << std::endl;

		int c = _getch();

		if (c == KEY_UP) {
			prevItem();
		}
		else if (c == KEY_DOWN) {
			nextItem();
		}
		else if (c == ENTER) {
			execItem();
		}
		else if (c == ESC) {
			terminate();
		}
#endif

	}


}

void GMenu::nextItem() {
	currentSelected = (currentSelected + 1) % items.size();
}

void GMenu::prevItem() {
	if 
		(currentSelected == 0) currentSelected = items.size() - 1;
	else
		currentSelected = (currentSelected - 1) % items.size();

}

void GMenu::terminate() {
	this->running = false;
}

void GMenu::execItem() {
	if (!items[currentSelected].isLocked()) {
		items[currentSelected].exec();
	}
	else {
		std::cout << "Unavalible" << std::endl;
		Input::prompt();
	}
}

void GMenu::unlockAll() {
	for (auto &i : items) {
		i.setLocked(false);
	}
}

void GMenu::clearScreen(){

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
	std::cout << "\033[2J\033[1;1H" << std::endl;
#elif _WIN32
	system("cls");
#else
	std::cout << std::string(100, '\n') << std::endl;
#endif
}
