#include "TransactionAccount.h"


float TransactionAccount::getCreditBalance() const {
	return m_creditBalance;
}
void TransactionAccount::setCreditBalance(float creditBalance) {
	m_creditBalance = creditBalance;
}

float TransactionAccount::getDisposableBalance() const {
	return m_creditBalance + getBalance();
}