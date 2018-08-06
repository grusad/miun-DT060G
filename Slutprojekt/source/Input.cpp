/*
* Filename:		Input.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Input.h"
#include <iostream>
#include <sstream>

// Returns a std::string as input.
std::string Input::GetString(const std::string& promt) 
{
	std::cout << promt << std::endl;
	std::string str;
	std::getline(std::cin, str);
	return str;

}

// Forces the user to input an integer
int Input::GetInteger(const std::string& promt) {

	while (std::cin) {

		std::stringstream ss(GetString(promt));
		int value;
		if (ss >> value)
		{
			//If valid input.
			return value;
		}

	}

	return -1;

}

float Input::GetFloat(const std::string& promt) {

	while (std::cin) {
		std::stringstream ss(GetString(promt));
		float value;
		if (ss >> value) {

			return value;
		}
	}

	return -1;
}

// Foces the user to input an integer within the tange of two values..
int Input::GetInteger(const std::string& promt, int min, int max) {

	while (true) {

		int	value = GetInteger(promt);
		if (value >= min && value <= max) return value;
	}

	return -1;

}

void Input::Prompt() {
	std::cout << "Enter any key to continue..." << std::endl;
	std::cin.get();
}

