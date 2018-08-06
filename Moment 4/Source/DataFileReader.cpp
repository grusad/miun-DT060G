/*
* Filename:		DataFileReader.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "DataFileReader.h"
#include <exception>

template <typename T>
DataFileReader<T>::DataFileReader(std::string dataFileName, std::string errorFileName) {
	fileName = dataFileName;
	errorName = errorFileName;
	filesOpen = false;
}

// Closes the streams.
template <typename T>
DataFileReader<T>::~DataFileReader() {
	dataFile.close();
	errorFile.close();
}
#include <iostream>

// Open the streams. Throws runtime_error exception if failed.
template <typename T>
void DataFileReader<T>::openFiles() {

	dataFile.open(fileName);
	errorFile.open(errorName);

	if (!dataFile.good() || !errorFile.good()) { // If failed.
		throw std::runtime_error("Failed to open files.");
	}
	else {

		std::ios_base::iostate mask = std::ios::eofbit | std::ios::failbit | std::ios::badbit;
		dataFile.exceptions(mask); // Sets the exceptionmask.

		filesOpen = true;

	}
	
}
// Reads the next value from file. 
template <typename T>
bool DataFileReader<T>::readNextValue(T &value) {

	if (filesOpen) {

		while (dataFile) { // While stream is good.

			try {
				dataFile >> value;
				return true;
			}
			catch (std::ios_base::failure &e) { // Catches any exceptions thrown by the filstream.
				auto flag = dataFile.rdstate();
				if (flag == std::ios::failbit || flag == std::ios::badbit) { // Reads the exceptionflag
					dataFile.clear();
					std::string str;
					dataFile >> str;
					errorFile << str << std::endl; // Print the failed data to errorfile.
				}
				if (flag == std::ios::eofbit) {
					return false;
				}
			}

		}
	}

	return false;
}

template<typename T>
bool DataFileReader<T>::isOpen() {
	return filesOpen;
}

