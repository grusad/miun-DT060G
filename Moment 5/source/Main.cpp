/*
* Filename:		Main.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "TestProgram.cpp"
#include "GMenu.h"

template <typename T>
void runTest(TestProgram<T> program);

int main() {

	GMenu menu("Choose the type.");
	menu.addItem(GItem("Integer",	[=]() { runTest(TestProgram<int>()); }, false));
	menu.addItem(GItem("Double",	[=]() { runTest(TestProgram<double>()); }, false));
	menu.addItem(GItem("EXIT",		[&menu]() { menu.terminate(); }, false));

	menu.showAndListen();

}

template <typename T>
void runTest(TestProgram<T> program) {


	GMenu menu("Choose operation");
	menu.addItem(GItem("Fill list",		[&program, &menu]() {program.fillList(); menu.unlockAll(); }, false));
	menu.addItem(GItem("Print list",	std::bind(&TestProgram<T>::printList, &program), false));
	menu.addItem(GItem("Print total",	std::bind(&TestProgram<T>::printTotal, &program), true));
	menu.addItem(GItem("Print between", std::bind(&TestProgram<T>::printBetween, &program, 1500, 1900), true));
	menu.addItem(GItem("Print max",		std::bind(&TestProgram<T>::printMax, &program), true));
	menu.addItem(GItem("Print min",		std::bind(&TestProgram<T>::printMin, &program), true));
	menu.addItem(GItem("Divide list",	std::bind(&TestProgram<T>::divide, &program, 2), true));
	menu.addItem(GItem("Reverse list",	std::bind(&TestProgram<T>::reverse, &program), true));
	menu.addItem(GItem("Sort list",		std::bind(&TestProgram<T>::sort, &program), true));
	menu.addItem(GItem("Write to file",	std::bind(&TestProgram<T>::writeToFile, &program, "file.txt"), true));
	menu.addItem(GItem("Read from file", [&program, &menu]() { if (program.readFromFile("file.txt")) menu.unlockAll(); }, false));
	menu.addItem(GItem("Clear list",	std::bind(&TestProgram<T>::clear, &program), true));
	menu.addItem(GItem("EXIT",			std::bind(&GMenu::terminate, &menu), false));
	
	menu.showAndListen();

}