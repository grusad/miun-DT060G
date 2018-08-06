#pragma once

#include "SavingsAccount.h"

class LongSavingsAccount : public SavingsAccount {

public:
	LongSavingsAccount(std::string accountNumber) : SavingsAccount(accountNumber) {
		m_interest += 0.02f; 
		m_maxWithdraw = 1;
		m_type = LONG_SAVINGS;
		
	};

};