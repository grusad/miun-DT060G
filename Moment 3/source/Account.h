/*
* Filename:		Account.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once
#include <vector>
#include <string>

enum Type {
	TRANSACTION, SAVINGS, LONG_SAVINGS
};

// A class that represents an Account for a customer of a bank.
class Account {

private:
	std::string m_accountNumber;
	float m_balance;

protected:
	Type m_type;

public:
	Account(std::string accountNumber, Type type);
	virtual ~Account() = 0;

	std::string getAccountNumber() const;
	void deposit(const float amount);

	float getBalance() const;
	void setBalance(float balance);

	virtual bool withdraw(const float amount);
	virtual float getDisposableBalance() const = 0;

	Type getType() const { return m_type; };

};