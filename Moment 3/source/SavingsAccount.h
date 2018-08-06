#pragma once

#include "Account.h"

class SavingsAccount : public Account {

protected:
	float m_interest;
	int m_maxWithdraw;
	int m_withdrawCount;

public:
	SavingsAccount(std::string accountNumber) :
		Account(accountNumber, SAVINGS), m_interest(0.02f), m_maxWithdraw(4), m_withdrawCount(0) {};

	float getInterest() const;
	void setInterest(float interest) { m_interest = interest; };
	bool withdraw(const float amount);
	int getMaxWithdraws() const;
	void setMaxWidthraws(int max)  { m_maxWithdraw = max; };

	float getDisposableBalance() const;

};