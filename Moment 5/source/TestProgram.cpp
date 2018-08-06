#include <list>
#include <random>
#include <ctime>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include <iterator>

#include "TestProgram.h"
#include <iostream>
#include "Input.h"



template <typename T>
TestProgram<T>::TestProgram() {
	list.resize(20);
}

template<typename T>
void TestProgram<T>::fillList(){

	std::default_random_engine generator((int)std::time(0));
	std::uniform_real_distribution<double> dist(1000, 2000);

	auto i = std::bind(dist, std::ref(generator));
	std::generate(list.begin(), list.end(), i);
	
	std::cout << "The list was filled with random numbers." << std::endl;
	Input::prompt();
}

template<typename T>
void TestProgram<T>::printList(){

	std::for_each(list.begin(), list.end(),
		[](const T t) {std::cout << t << std::endl; });

	Input::prompt();

}

template<typename T>
void TestProgram<T>::printTotal(){

	T t = std::accumulate(list.begin(), list.end(), 0.0);
	std::cout << "Total: " << t << std::endl;
	Input::prompt();

}

template<typename T>
void TestProgram<T>::printAvarage(){

	T t = std::accumulate(list.begin(), list.end(), 0.0) / list.size();
	std::cout << "Avarage: " << t << std::endl;
	Input::prompt();

}

template<typename T>
void TestProgram<T>::printBetween(T min, T high){

	auto i = std::find_if(list.begin(), list.end(),
		[min, high](T value) { return value >= min && value <= high; });
	std::cout << "Value found: " << *i << std::endl;
	Input::prompt();
	
}

template<typename T>
void TestProgram<T>::printMax(){

	auto t = std::max_element(list.begin(), list.end());
	std::cout << "Max: " << *t << std::endl;
	Input::prompt();
}

template<typename T>
void TestProgram<T>::printMin(){

	auto t = std::min_element(list.begin(), list.end());
	std::cout << "Min: " << *t << std::endl;
	Input::prompt();
}

template<typename T>
void TestProgram<T>::divide(T diviator){

	std::transform(list.begin(), list.end(), list.begin(), std::bind2nd(std::divides<T>(), diviator));
	std::cout << "The element was divided by " << diviator << "." << std::endl;
	Input::prompt();
}

template<typename T>
void TestProgram<T>::reverse(){

	auto begin = list.begin();
	auto end = list.end();

	while ((begin != end) && (begin != --end)) {
		std::iter_swap(begin++, end);
	}

	std::cout << "The list was reversed." << std::endl;
	Input::prompt();

}

template<typename T>
void TestProgram<T>::sort(){

	list.sort();
	std::cout << "The list was sorted." << std::endl;
	Input::prompt();
}

template<typename T>
void TestProgram<T>::writeToFile(std::string fileName){

	std::ofstream file(fileName);
	if (file.is_open()) {
		std::copy(list.begin(), list.end(), std::ostream_iterator<T>(file, "\n"));
		file.close();
		std::cout << "The list was saved to file." << std::endl;
	}
	else {
		std::cout << "The list was NOT saved to file." << std::endl;
	}

	Input::prompt();

}

template<typename T>
bool TestProgram<T>::readFromFile(std::string fileName){

	std::ifstream file(fileName);
	if (file.is_open()) {
		list.clear();
		std::copy(std::istream_iterator<T>(file), std::istream_iterator<T>(),
			std::back_inserter(list));
		file.close();
		std::cout << "The list was loaded from file." << std::endl;
		Input::prompt();
		return true;
	}
	else {
		std::cout << "The list was NOT loaded from file." << std::endl;
		Input::prompt();
		return false;
	}



}

template<typename T>
void TestProgram<T>::clear(){
	list.clear();

	std::cout << "The list was cleared." << std::endl;
	Input::prompt();
}

