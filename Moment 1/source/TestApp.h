/*
* Filename:		TestApp.h
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#ifndef _TESTAPP
#define _TESTAPP

#include <memory>
#include "Queue.h"
#include "Menu.h"

class TestApp {

private:
	std::unique_ptr<Queue> queuePtr;
	Menu menu;

	void printMenu();
	void createQueue();
	void enqueue();
	void dequeue();

	void printQueueInfo() const;


public:
	void run();

};

#endif 