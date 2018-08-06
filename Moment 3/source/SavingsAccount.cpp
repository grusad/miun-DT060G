#include "SavingsAccount.h"

float SavingsAccount::getInterest() const {
	return m_interest;
}

bool SavingsAccount::withdraw(const float amount) {
	if (m_withdrawCount != m_maxWithdraw) {
		m_withdrawCount++;
		return Account::withdraw(amount);
	}
	return false;
}

int SavingsAccount::getMaxWithdraws() const {
	return m_maxWithdraw;
}

float SavingsAccount::getDisposableBalance() const {
	return getBalance();
}