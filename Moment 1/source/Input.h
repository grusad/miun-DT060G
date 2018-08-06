/*
* Filename:		Input.h
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/

#pragma once

#include <string>

class Input {

public:

	static std::string getString();
	static int getInteger();
	static int getInteger(int min, int max);
	static void prompt();
};