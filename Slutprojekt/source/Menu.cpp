/*
* Filename:		Menu.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Menu.h"
#include <iostream>
#include <functional>
#include "MenuItem.h"
#include "Input.h"


// show the menu as a sub menu
void Menu::ShowSub()
{

	int input;

	do
	{
		ClearScreen();

		std::cout << "-" << name << "-\n" << std::endl;

		for (auto& item : items)
		{
			
			std::cout << item.first << ": " << item.second.GetName() << std::endl;
			
		}

		std::cout << items.size() + 1 << ": Return" << std::endl;

		input = Input::GetInteger("", 1, static_cast<int>(items.size() + 1));

		if (input == items.size() + 1)
		{
			break;
		}
	
		items.at(input).Exec();
		

	} while (true);
}

// show the menu as a main menu.
void Menu::ShowMain()
{
	int input;

	do
	{
		ClearScreen();

		std::cout << "-" << name << "-\n" << std::endl;

		for (auto& item : items)
		{

			std::cout << item.first << ": " << item.second.GetName() << std::endl;

		}

		std::cout << items.size() + 1 << ": Exit" << std::endl;

		input = Input::GetInteger("", 1, static_cast<int>(items.size() + 1));

		if (input == items.size() + 1)
		{
			break;
		}

		items.at(input).Exec();


	} while (input >= 1 && input <= items.size());
}


void Menu::AddItem(MenuItem item, int index)
{
	items[index] = item;
}

void Menu::SetItemState(int id, bool active)
{
	items.at(id).SetState(active);
}

// clears the screen depending on OS
void Menu::ClearScreen()
{
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
	std::cout << "\033[2J\033[1;1H" << std::endl;
#elif _WIN32
	system("cls");
#else
	std::cout << std::string(100, '\n') << std::endl;
#endif
}