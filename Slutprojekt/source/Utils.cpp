/*
* Filename:		Utils.cpp
* Course:		DT060G Objektorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Utils.h"
#include <algorithm>

std::string Utils::ToLower(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;
}
