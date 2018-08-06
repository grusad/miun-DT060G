#pragma once

#include "Account.h"

class TransactionAccount : public Account {

private:

	float m_creditBalance;

public:

	TransactionAccount(std::string accountNumber)
		: Account(accountNumber, TRANSACTION), m_creditBalance(0) {};


	float getCreditBalance() const;
	void setCreditBalance(float creditBalance);

	float getDisposableBalance() const;
};