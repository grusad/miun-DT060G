/*
* Filename:		Input.cpp
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#include "Input.h"
#include <iostream>
#include <sstream>

// Returns a std::string as input.
std::string Input::getString() {

	std::string str;
	std::getline(std::cin, str);
	return str;

}

// Forces the user to input an integer
int Input::getInteger() {
	
	while (std::cin) {

		std::stringstream ss(getString());
		int value;
		if (ss >> value)
		{
			//If valid input.
			return value;
		}

	}

	return -1;

}

// Foces the user to input an integer within the tange of two values..
int Input::getInteger(int min, int max) {
	
	while (true) {

		int	value = getInteger();
		if (value >= min && value <= max) return value;
	}

	return -1;

}

void Input::prompt() {
	std::cout << "Enter any key to continue..." << std::endl;
	getString();
}