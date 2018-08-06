/*
* Filename:		Bank.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once

#include "BankClient.h"

// A class that represents a Bank sercing different customers/clients.
class Bank {

private:
	std::unique_ptr<BankClient> client; //Current customer/client being served.

public:

	bool loadCustomer(const std::string id);
	bool createNewCustomer(const std::string id, const std::string firstName, const std::string lastName);

	std::string getCustomersName() const;
	std::string getCustomersID() const;
	int getNrOfCustomersAccounts() const;
	std::vector<std::string> getCustomersAccountNumbers() const;
	float getCustomersTotalAssets() const;
	bool getCustomersAccountInfo(const std::string accountNumber, float &balance, float &credit, float &disposalBalance, float &interest, int &withdrawCount, Type &type) const;
	bool withdrawCustomer(std::string accountNumber, const float amount) const;
	bool depositCustomer(std::string accountNumber, const float amount) const;
	bool setCustomersCreditBalanace(std::string accountNumber, const float amount);
	bool createNewCustomerAccount(const Type type);
	bool removeCustomersAccount(const std::string accountNumber);
	void changeCustomer();
	bool hasClientCurrently() const { return client.get() != nullptr; };
	
};