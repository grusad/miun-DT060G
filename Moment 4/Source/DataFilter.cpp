/*
* Filename:		DataFilter.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "DataFilter.h"
#include <sstream>

template <typename T>
DataFilter<T>::DataFilter(DataFileReader<T>* reader, T min, T max) {
	m_reader = reader;
	m_min = min;
	m_max = max;
	dataFile.open("RangeErrors.dat");
	hasReturnedFalse = false;
	rangeErrorCount = 0;
}

// Closes streams.
template <typename T>
DataFilter<T>::~DataFilter() {
	dataFile.close();
}

// Gets the next value by the reader
template <typename T>
bool DataFilter<T>::getNextValue(T &value) {
	
	if (!hasReturnedFalse) { // If false has never been returned
		
		if (m_reader->readNextValue(value)) {

			try {

				if (value < m_min || value > m_max) { // If out of bounds.
					std::stringstream ss;
					ss << value; // Write to stream.
					throw std::range_error(ss.str());
				}
			}
			catch (std::range_error &e) { // Catches exception thrown by the try block.
				dataFile << e.what() << std::endl; // Write to file.
				rangeErrorCount++;
				getNextValue(value); // Calls the funkton again to read a new value and filter the value.
			}
			
			return true;
		}
	}

	hasReturnedFalse = true;
	return false;


}

template <typename T>
int DataFilter<T>::getRangeErrorCount() const {
	return rangeErrorCount;
}