/*
* Filename:		TestApp.cpp
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#include "TestApp.h"
#include "Input.h"
#include <iomanip>
#include <iostream>

void TestApp::printMenu() {


	menu.add(MenuItem("Create queue.", true));
	menu.add(MenuItem("Add to queueu.", false));
	menu.add(MenuItem("Remove from queue.", false));
	menu.add(MenuItem("Print queue-info.", false));
	menu.add(MenuItem("Exit.", true));

	bool running = true;

	while (running) {

		menu.print();

		switch (menu.getAlternative()) {

		case 1:
			createQueue();
			break;
		case 2:
			enqueue();
			break;
		case 3:
			dequeue();
			break;
		case 4:
			printQueueInfo();
			break;
		case 5:
			running = false;
			break;

		}
	

	}

}

void TestApp::createQueue() {

	std::cout << "**** CREATE QUEUE ****" << std::endl;
	std::cout << "Enter queuesize: "; 
	int size = Input::getInteger();

	//Creates a new unique pointer...
	queuePtr = std::unique_ptr<Queue>(new Queue(size));
	menu.enableAll();	// All alternatives in the menu is avalible after this line.

	std::cout << "Queue created..." << std::endl;
	Input::prompt();
}

void TestApp::enqueue() {

	// If queue is full...
	if (queuePtr->isFull()) {
		std::cout << "The queue is full." << std::endl;
		Input::prompt();
		return;
	}

	// Good to go...
	std::cout << "**** ADD TO QUEUE ****" << std::endl;
	std::cout << "Enter an integer: ";
	int value = Input::getInteger();

	queuePtr->enqueue(value);

	std::cout << "Added to queue." << std::endl;
	Input::prompt();


}

void TestApp::dequeue() {

	// If queue is empty...
	if (queuePtr->isEmpty()) {
		std::cout << "The queue is empty..." << std::endl;
		Input::prompt();
		return;
	}

	// Good to go...
	Item item;
	queuePtr->dequeue(item);
	
	std::cout << item << " was removed." << std::endl;
	
}

void TestApp::printQueueInfo() const {

	std::cout << std::setw(16) << "Is full: " << queuePtr->isFull() << std::endl;
	std::cout << std::setw(16) << "Is empty: " << queuePtr->isEmpty() << std::endl;
	std::cout << std::setw(16) << "Current size: " << queuePtr->getLength() << std::endl;
	std::cout << std::setw(16) << "Capacity: " << queuePtr->getCapacity() << std::endl;

	Input::prompt();
}

void TestApp::run() {

	printMenu();

}