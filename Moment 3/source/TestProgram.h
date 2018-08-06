/*
* Filename:		TestProgram.h
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#pragma once
#include "Bank.h"
#include "Menu.h"


// A testclass to handle the Bank.
class TestProgram {

private:
	Bank bank;
	Menu startMenu, mainMenu;

public:

	TestProgram();
	void runStart();

private:
	void runMenu();
	void printName() const;
	void printID() const;
	void printNrOfAccounts() const;
	void printTotalAssets() const;
	void printSummary();
	void printAccountInfo(const Type type,const float balance, const float credit, const float disposable, float interest, int maxWidthraw) const;
	void printAccounts() const;

	void loadNewCustomer();
	void createNewCustomer();
	void selectAccountToInfo();
	void withdraw();
	void deposit();
	void credit();
	void createAccount();
	void removeAccount();
	void saveAndLeave();

	bool hasNoAccounts() const;

};

void clearScreen();