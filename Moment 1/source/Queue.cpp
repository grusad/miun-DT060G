/*
* Filename:		Queue.cpp
* Course:		DT019G Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
* Date:			2018-03-26
*/


#include "Queue.h"

Queue::Queue(const int maxSize) : m_ptr(new Item[maxSize]){
	m_maxSize = maxSize;
	m_head = 0;
	m_tail = 0;
	m_currentSize = 0;
}

void Queue::enqueue(Item item) {

	if (!isFull()) {

		m_ptr[m_tail] = item;
		m_tail = (m_tail + 1) % m_maxSize;	// Moves m_tail to the next index. '%' makes the array circular.
		m_currentSize++;

	}

}

void Queue::dequeue(Item &item) {

	if (!isEmpty()) {

		item = m_ptr[m_head];
		m_head = (m_head + 1) % m_maxSize; // Moves m_head to the next index. '%' makes the array circular.
		m_currentSize--;
	}

}
