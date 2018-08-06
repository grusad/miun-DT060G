/*
* Filename:		BankClient.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "BankClient.h"
#include <algorithm>
#include <fstream>

// Return a vector of strings containing the clients account numbers.
std::vector<std::string> BankClient::getAccountNumbers() const {

	std::vector<std::string> accountNumbers;

	for (auto &i : m_accounts)
		accountNumbers.push_back(i->getAccountNumber());

	return accountNumbers;

}

// Returns the total assets of all accounts combined.
float BankClient::getTotalAssets() const {

	float total = 0;

	for (auto &i : m_accounts) {
		total += i->getBalance();
	}
	
	return total;
}

// Sets the reference values by a certain account numbedr.
bool BankClient::getAccountInfo(const std::string accountNumber, float &balance, float &credit, float &disposalBalance) const {

	for (auto &i : m_accounts) {
		if (i->getAccountNumber() == accountNumber) {
			balance = i->getBalance();
			credit = i->getCreditBalance();
			disposalBalance = i->getDisposableBalance();
			return true;
		}
	}

	return false;
}

// Creates a new account for the client.
bool BankClient::createNewAccount() {

	if (getNrOfAccount() != MAX_ACCOUNTS) { // If current amount of accounts not equal the maximum number of accounts.
		std::string accountNumber = m_ID + "-" + std::to_string(getNrOfAccount());	// Creates the account number by the clients id and the clients total amount of accounts (Always unique).
		m_accounts.push_back(std::unique_ptr<Account>(new Account(accountNumber)));
		return true;
	}

	return false;
}

// Removes an account by the given account number as parameter
bool BankClient::removeAccount(std::string accountNumber) {
	
	auto i = std::find_if(m_accounts.begin(), m_accounts.end(),
		[accountNumber](const std::unique_ptr<Account> &account) { return account->getAccountNumber() == accountNumber; });
	if (i != m_accounts.end()) { // If account number found by the algoritm
		m_accounts.erase(i);
		return true;
	}
	return false;
}

// Withdraws money from account number.
bool BankClient::withdraw(std::string accountNumber, const float amount) {

	for (auto &i : m_accounts) {
		if (i->getAccountNumber() == accountNumber) {
			return i->withdraw(amount);
		}
	}
	
	return false;
}

// Depsoit money to account number.
bool BankClient::deposit(std::string accountNumber, const float amount) {

	for (auto &i : m_accounts) {
		if (i->getAccountNumber() == accountNumber) {
			i->deposit(amount);
			return true;
		}
	}

	return false;

}

// Sets the credit balance to an account number.
bool BankClient::setCreditBalance(std::string accountNumber, const float amount) {

	for (auto &i : m_accounts) {
		if (i->getAccountNumber() == accountNumber) {
			i->setCreditBalance(amount);
			return true;
		}
	}

	return false;
}

// Returns all accounts with all its data as a referenced map-object.
void BankClient::getSummary(std::map <std::string, std::vector<int>> &map) {
	for (auto &i : m_accounts) {
		std::vector<int> summary;
		summary.push_back(i->getBalance());
		summary.push_back(i->getCreditBalance());
		summary.push_back(i->getDisposableBalance());
		map[i->getAccountNumber()] = summary;
	}
}


bool BankClient::saveToFile() {

	std::ofstream file(m_ID + ".knt");

	if (file.is_open()) {

		file << m_firstName << std::endl << m_lastName << std::endl << m_ID << std::endl;

		for (auto &i : m_accounts) {
			file << i->getAccountNumber() << std::endl
				<< i->getBalance() << std::endl
				<< i->getCreditBalance() << std::endl;
		}

		file.close();
		return true;
	}

	return false;

}

bool BankClient::readFromFile(const std::string id) {

	std::ifstream file(id + ".knt");

	if (file.is_open()) {

		std::getline(file, m_firstName);
		std::getline(file, m_lastName);
		std::getline(file, m_ID);

		std::string tempAcc;
		float  tempBal;
		float tempCre;

		while (std::getline(file, tempAcc)) {

			file >> tempBal;
			file >> tempCre;
			file.get();

			m_accounts.push_back(std::unique_ptr<Account>(new Account(tempAcc, tempBal, tempCre)));

		}

		file.close();

		return true;

	}

	return false;
}