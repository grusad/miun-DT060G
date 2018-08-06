/*
* Filename:		Account.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Account.h"

Account::Account(std::string accountNumber, Type type) {
	m_accountNumber = accountNumber;
	m_balance = 0;
	m_type = type;
}

Account::~Account() {};

void Account::deposit(const float amount) {

	m_balance += amount;
}

bool Account::withdraw(const float amount) {

	if (getDisposableBalance() >= amount) {	// If current disposable balance is greater than the amount to withdraw
		m_balance -= amount;
		return true;
	}
	return false;
}

std::string Account::getAccountNumber() const {
	return m_accountNumber; 
}

float Account::getBalance() const {
	return m_balance;
}

void Account::setBalance(float balance) {
	m_balance = balance;
}
