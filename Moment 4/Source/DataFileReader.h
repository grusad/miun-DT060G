/*
* Filename:		DataFileReader.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#ifndef DATA_FILE_READER
#define DATA_FILE_READER

#include <string>
#include <fstream>

// A templateclass used to read data from file.
template <typename T>
class DataFileReader {

private:
	std::string fileName;
	std::string errorName;

	std::ifstream dataFile;
	std::ofstream errorFile;

	bool filesOpen;

public:

	DataFileReader(std::string dataFileName, std::string errorFileName);
	~DataFileReader();

	void openFiles();
	bool readNextValue(T &value);
	bool isOpen();

};


#endif 


