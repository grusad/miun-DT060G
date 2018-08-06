/*
* Filename:		Account.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once
#include <vector>
#include <string>

// A class that represents an Account for a customer of a bank.
class Account {

private:

	std::string m_accountNumber;
	float m_balance;
	float m_creditBalance;

public:
	Account(std::string accountNumber) : m_accountNumber(accountNumber), m_balance(0), m_creditBalance(0) {};
	Account(std::string accountNumber, float balance, float creditBalance)
		: m_accountNumber(accountNumber), m_balance(balance), m_creditBalance(creditBalance) {};

	void deposit(const float amount);
	bool withdraw(const float amount);
	float getCreditBalance() const { return m_creditBalance; };
	void setCreditBalance(float creditBalance) { m_creditBalance = creditBalance; };
	float getBalance() const { return m_balance; };
	float getDisposableBalance() const { return m_balance + m_creditBalance; };
	std::string getAccountNumber() const { return m_accountNumber; };

};