/*
* Filename:		Account.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/

#include "Account.h"

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