#pragma once

#pragma once

#include <string>

class Input {

public:

	static std::string getString();
	static int getInteger();
	static float getFloat();
	static int getInteger(int min, int max);
	static void prompt();
};