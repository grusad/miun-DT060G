/*
* Filename:		Input.h
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef INPUT_H
#define INPUT_H

#include <string>

// Input class
class Input 
{
public:

	static std::string GetString(const std::string& promt);
	static int GetInteger(const std::string& promt);
	static float GetFloat(const std::string& promt);
	static int GetInteger(const std::string& promt, int min, int max);
	static void Prompt();
};

#endif