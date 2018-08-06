/*
* Filename:		Queue.h
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#pragma once

#include <memory>

typedef int Item;

const int defaultSize = 10;

class Queue {

private:
	std::unique_ptr<Item[]> m_ptr;
	int m_head;
	int m_tail;
	int m_currentSize;
	int m_maxSize;

public:
	Queue(const int maxSize = defaultSize);
	void enqueue(Item item);
	void dequeue(Item &item);
	int getLength() const { return m_currentSize; };
	bool isFull() const { return m_currentSize == m_maxSize; };
	bool isEmpty() const { return m_currentSize == 0; };
	int getCapacity() const { return m_maxSize; };

};

