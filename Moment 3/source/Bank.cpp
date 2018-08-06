/*
* Filename:		Bank.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "Bank.h"

bool Bank::createNewCustomer(const std::string id, const std::string firstName, const std::string lastName) {
	client.reset(new BankClient()); // Sets the unique pointer to point at a new customer object
	client->setFirstName(firstName);
	client->setLastName(lastName);
	client->setID(id);
	return true;
}

bool Bank::loadCustomer(const std::string id) {
	client.reset(new BankClient());	//Sets the unique pointer to point at a new customer object
	return client->readFromFile(id);// Load the data from file. Returns true if successfull.
}

std::string Bank::getCustomersName() const {
	return client->getFirstName() + " " + client->getLastName();
}

std::string Bank::getCustomersID() const {
	return client->getID();
}

int Bank::getNrOfCustomersAccounts() const {
	return client->getNrOfAccount();
}

std::vector<std::string> Bank::getCustomersAccountNumbers() const {
	return client->getAccountNumbers();
}

float Bank::getCustomersTotalAssets() const {
	return client->getTotalAssets();
}

bool Bank::getCustomersAccountInfo(const std::string accountNumber, float &balance, float &credit, float &disposalBalance, float &interest, int &withdrawCount, Type &type) const {
	return client->getAccountInfo(accountNumber,  balance, credit, disposalBalance, interest, withdrawCount, type);
}

bool Bank::withdrawCustomer(std::string accountNumber, const float amount) const {
	return client->withdraw(accountNumber, amount);
}

bool Bank::depositCustomer(std::string accountNumber, const float amount) const {
	return client->deposit(accountNumber, amount);
}

bool Bank::setCustomersCreditBalanace(std::string accountNumber, const float amount) {
	return client->setCreditBalance(accountNumber, amount);
}

bool Bank::createNewCustomerAccount(const Type type) {
	return client->createNewAccount(type);
}

bool Bank::removeCustomersAccount(const std::string accountNumber) {
	return client->removeAccount(accountNumber);
}

void Bank::changeCustomer() {
	client->saveToFile();	// Saves current client to file.
	client.reset();			// Deallocate the object that the pointer holds.
}