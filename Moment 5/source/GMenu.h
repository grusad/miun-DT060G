#pragma once

#include <vector>
#include "GItem.h"

class GMenu {

private:
	std::string title;
	std::vector<GItem> items;
	int currentSelected;
	bool running;

public:

	GMenu(const std::string title);
	GMenu();

	void addItem(GItem item);
	void showAndListen();
	void setTitle(const std::string title);
	void terminate();
	void unlockAll();

private:

	void clearScreen();
	void nextItem();
	void prevItem();
	void execItem();


};