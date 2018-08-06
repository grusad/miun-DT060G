/*
* Filename:		DataFilter.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#ifndef DATA_FILTER
#define DATA_FILTER

#include "DataFileReader.h"


// A class that filters the data to read.
template <typename T>
class DataFilter {

private:
	DataFileReader<T> *m_reader; // A pointer to a filereader.
	T m_min, m_max;
	bool hasReturnedFalse;
	std::ofstream dataFile;
	int rangeErrorCount;

public:
	DataFilter(DataFileReader<T>* reader, T min, T max);
	~DataFilter();

	bool getNextValue(T &value);
	int getRangeErrorCount() const;

};


#endif 


