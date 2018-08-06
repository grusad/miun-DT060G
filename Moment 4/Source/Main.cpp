/*
* Filename:		Main.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include <iostream>
#include "DataFilter.cpp"
#include "DataFileReader.cpp"

int main() {

	typedef double Type;
	DataFileReader<Type> reader("Values.dat", "ReadErrors.dat");
	try {
		reader.openFiles();
	}
	catch (std::runtime_error &e) { // If openFiles fails.
		std::cout << e.what();
		std::cin.get();
		return -1;
	}
	DataFilter<Type> filter(&reader, 0.0, 10.0);

	Type value;
	double sum = 0;
	int counter = 0;
	while (filter.getNextValue(value)) {

		sum += value;
		counter++;
	}

	std::cout << "Total: "<< sum << std::endl;
	std::cout << "Avarage: " << sum / counter << std::endl;
	std::cout << "Amount: " << counter << std::endl;
	std::cout << "Amount of data out of range: " << filter.getRangeErrorCount() << std::endl;
	

	std::cin.get();


	return 0;

}
