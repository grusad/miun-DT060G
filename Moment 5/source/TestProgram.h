#pragma once

#include <string>
#include <list>

template <typename T>
class TestProgram {

private:
	std::list<T> list;

public:

	TestProgram();

	void fillList();
	void printList();
	void printTotal();
	void printAvarage();
	void printBetween(T min, T max);
	void printMax();
	void printMin();
	void divide(T diviator);
	void reverse();
	void sort();
	void writeToFile(std::string fileName);
	bool readFromFile(std::string fileName);
	void clear();

	
};