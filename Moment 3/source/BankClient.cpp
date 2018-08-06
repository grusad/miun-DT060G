/*
* Filename:		BankClient.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "BankClient.h"
#include <algorithm>
#include <fstream>
#include "TransactionAccount.h"
#include "SavingsAccount.h"
#include "LongSavingsAccount.h"

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
bool BankClient::getAccountInfo(const std::string accountNumber, float &balance, float &credit, float &disposalBalance, float &interest, int &withdrawCount, Type &type) const {

	for (auto &i : m_accounts) {
		if (i->getAccountNumber() == accountNumber) {
			balance = i->getBalance();
			disposalBalance = i->getDisposableBalance();
			type = i->getType();

			if (TransactionAccount* ptr = dynamic_cast<TransactionAccount*> (&(*i))) {
				credit = ptr->getCreditBalance();
			}

			if (SavingsAccount* ptr = dynamic_cast<SavingsAccount*>(&(*i))) {
				interest = ptr->getInterest();
				withdrawCount = ptr->getMaxWithdraws();
			}

			return true;
		}
	}

	return false;
}

// Creates a new account for the client.
bool BankClient::createNewAccount(const Type type) {

	if (getNrOfAccount() != MAX_ACCOUNTS) { // If current amount of accounts not equal the maximum number of accounts.
		std::string accountNumber = m_ID + "-" + std::to_string(getNrOfAccount());	// Creates the account number by the clients id and the clients total amount of accounts (Always unique).

		switch (type) {
		case TRANSACTION:
			m_accounts.push_back(std::unique_ptr<Account>(new TransactionAccount(accountNumber)));
			break;
		case SAVINGS:
			m_accounts.push_back(std::unique_ptr<Account>(new SavingsAccount(accountNumber)));
			break;
		case LONG_SAVINGS:
			m_accounts.push_back(std::unique_ptr<Account>(new LongSavingsAccount(accountNumber)));
			break;
		}

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
			if (TransactionAccount* ptr = dynamic_cast<TransactionAccount*>(&(*i))){
				ptr->setCreditBalance(amount);
				return true;
			}
		}
	}

	return false;
}


bool BankClient::saveToFile() {

	std::ofstream file(m_ID + ".knt");

	if (file.is_open()) {

		file << m_firstName << std::endl << m_lastName << std::endl << m_ID << std::endl;

		for (auto &i : m_accounts) {

			file << i->getAccountNumber() << std::endl;

			Type type = i->getType();
			file << type << std::endl;

			file << i->getBalance() << std::endl;

			if (type == TRANSACTION) {
				TransactionAccount* ptr = dynamic_cast<TransactionAccount*>(&(*i));
				file << ptr->getCreditBalance() << std::endl;
			}
			if (type == SAVINGS || type == LONG_SAVINGS) {
				SavingsAccount* ptr = dynamic_cast<SavingsAccount*>(&(*i));
				file << ptr->getMaxWithdraws() << std::endl;
				file << ptr->getInterest() << std::endl;
			}
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
		float tempInt;
		int tempWid;
		int tempType;

		while (std::getline(file, tempAcc)) {

			file >> tempType;
			file >> tempBal;

			if (tempType == TRANSACTION) {
				file >> tempCre;
				m_accounts.push_back(std::unique_ptr<Account>(new TransactionAccount(tempAcc)));
				TransactionAccount* ptr = dynamic_cast<TransactionAccount*>(&(*m_accounts[m_accounts.size() - 1]));
				ptr->setCreditBalance(tempCre);
				ptr->setBalance(tempBal);
			}
			else {
				file >> tempWid;
				file >> tempInt;
			}

			if (tempType == SAVINGS) {
				m_accounts.push_back(std::unique_ptr<Account>(new SavingsAccount(tempAcc)));
				SavingsAccount* ptr = dynamic_cast<SavingsAccount*>(&(*m_accounts[m_accounts.size() - 1]));
				ptr->setMaxWidthraws(tempWid);
				ptr->setInterest(tempInt);
				ptr->setBalance(tempBal);
			}

			if (tempType == LONG_SAVINGS) {
				m_accounts.push_back(std::unique_ptr<Account>(new LongSavingsAccount(tempAcc)));
				LongSavingsAccount* ptr = dynamic_cast<LongSavingsAccount*>(&(*m_accounts[m_accounts.size() - 1]));
				ptr->setMaxWidthraws(tempWid);
				ptr->setInterest(tempInt);
				ptr->setBalance(tempBal);
			}

			file.get();

		}

		file.close();

		return true;

	}

	return false;
}
