/*
* Filename:		BankClient.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Account.h"

// A class that represents a customer/client of a bank
class BankClient {

private:

	const int MAX_ACCOUNTS = 3;	// Maximum amount of accounts.

	std::string m_firstName, m_lastName;
	std::string m_ID;
	std::vector<std::unique_ptr<Account>> m_accounts;

public:
	BankClient() : m_firstName(""), m_lastName(""), m_ID("") {};
	BankClient(std::string firstName, std::string lastName, std::string ID)
		: m_firstName(firstName), m_lastName(lastName), m_ID(ID) {};

	std::string getFirstName() const	{ return m_firstName; };
	std::string getLastName() const		{ return m_lastName; };
	std::string getID() const			{ return m_ID; };

	void setFirstName(const std::string firstName)		{ m_firstName = firstName; };
	void setLastName(const std::string lastName)		{ m_lastName = lastName; };
	void setID(const std::string ID)					{ m_ID = ID; };

	int getNrOfAccount() const { return m_accounts.size(); };
	std::vector<std::string> getAccountNumbers() const;
	float getTotalAssets() const;
	bool getAccountInfo(const std::string accountNumber, float &balance, float &credit, float &disposalBalance) const;
	void getSummary(std::map <std::string, std::vector<int>> &map);

	bool createNewAccount();
	bool removeAccount(std::string accountNumber);
	bool withdraw(std::string accountNumber, const float amount);
	bool deposit(std::string accountNumber, const float amount);
	bool setCreditBalance(std::string accountNumber, const float amount);

	bool saveToFile();
	bool readFromFile(const std::string id);

};