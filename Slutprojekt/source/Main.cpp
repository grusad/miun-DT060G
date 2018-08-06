/*
* Filename:		Main.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Application.h"
#include <iostream>

int main()
{
	try
	{
		Application application;
		application.ShowMenu();
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
	}
}