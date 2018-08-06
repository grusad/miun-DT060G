/*
* Filename:		TestProgram.cpp
* Course:		Objectorienterad Programmering i C++
* Author:		Alexander Gillberg
* ID:			algi1701
*/


#include "TestProgram.h"
#include "Input.h"
#include <iostream>
#include <functional>

// Initalizes all the menus.
TestProgram::TestProgram() {

	startMenu.add(MenuItem("Load customer from file.", true));
	startMenu.add(MenuItem("Create a new customer.", true));
	startMenu.add(MenuItem("Quit.", true));

	mainMenu.add(MenuItem("Customer name.", true));
	mainMenu.add(MenuItem("Customer id.", true));
	mainMenu.add(MenuItem("Number of accounts.", true));
	mainMenu.add(MenuItem("Account numbers.", true));
	mainMenu.add(MenuItem("Total assets.", true));
	mainMenu.add(MenuItem("Account info.", true));
	mainMenu.add(MenuItem("Withdraw.", true));
	mainMenu.add(MenuItem("Deposit.", true));
	mainMenu.add(MenuItem("Set credit.", true));
	mainMenu.add(MenuItem("Accounts summary.", true));
	mainMenu.add(MenuItem("Create new account.", true));
	mainMenu.add(MenuItem("Remove account.", true));
	mainMenu.add(MenuItem("Change customer.", true));
	mainMenu.add(MenuItem("Quit.", true));


}

// Startfunction with loop
void TestProgram::runStart() {

	using FunctionCall = std::function<void(TestProgram&)>;	// functionpointer.
	using FunctionMap = std::map<int, FunctionCall>;		// map with an index and the functionpointer

	const FunctionMap funcMap{								// Fills the map
		{1, &TestProgram::loadNewCustomer},
		{2, &TestProgram::createNewCustomer},
	};

	while (true) {

		clearScreen();
		startMenu.print();

		int alternative = startMenu.getAlternative();
		if (alternative == 3) break;	// If quit

		const auto &i = funcMap.find(alternative);	//Find the corresponding function to the given input
		if (i != funcMap.end()) i->second(*this);	//Runs it.
	}

}

// The function with the main loop
void TestProgram::runMenu() {

	using FunctionCall = std::function<void(TestProgram&)>;	//Functionpointer
	using FunctionMap = std::map<int, FunctionCall>;		//map with an index and the functionpointer

	const FunctionMap funcMap{								//Fills the map
		{ 1, &TestProgram::printName },
		{ 2, &TestProgram::printID },
		{ 3, &TestProgram::printNrOfAccounts },
		{ 4, &TestProgram::printAccounts },
		{ 5, &TestProgram::printTotalAssets },
		{ 6, &TestProgram::selectAccountToInfo },
		{ 7, &TestProgram::withdraw },
		{ 8, &TestProgram::deposit },
		{ 9, &TestProgram::credit },
		{ 10, &TestProgram::printSummary },
		{ 11, &TestProgram::createAccount },
		{ 12, &TestProgram::removeAccount },
		{ 13, &TestProgram::saveAndLeave },
		{ 14, &TestProgram::saveAndLeave },

	};

	while (true) {

		if (!bank.hasClientCurrently()) {	//If no client/customer is set return to the previous menu.
			break;
		}

		clearScreen();
		mainMenu.print();

		const auto &i = funcMap.find(mainMenu.getAlternative());//Find the corresponding function to the given input
		if(i != funcMap.end()) i->second(*this);				//Runs it

		Input::prompt();

	}

}

//Loads a new customer/client to the bank
void TestProgram::loadNewCustomer() {

	std::cout << "Enter ID [YYMMDD-XXXX]: ";
	if (bank.loadCustomer(Input::getString())) {
		std::cout << "Successfully loaded customer." << std::endl;
		Input::prompt();
		runMenu();
	}
	else {
		std::cout << "Could not load customer by the given id." << std::endl;
		Input::prompt();
	}
}

//Creates a new customer/client to the bank.
void TestProgram::createNewCustomer() {

	std::cout << "Enter the personal ID for the customer: ";
	std::string id = Input::getString();
	std::cout << "Enter firstname: ";
	std::string firstName = Input::getString();
	std::cout << "Enter lastname: ";
	std::string lastName = Input::getString();

	std::cout << "Customer created." << std::endl;
	Input::prompt();

	bank.createNewCustomer(id, firstName, lastName);
	runMenu();
}

// Shows information about a given account 
void TestProgram::selectAccountToInfo() {

	if (hasNoAccounts()) return;	

	printAccounts();

	std::cout << "Which account do you want information about? " << std::endl;
	float balance, credit, disposable;

	if (bank.getCustomersAccountInfo(Input::getString(), balance, credit, disposable)) {
		printAccountInfo(balance, credit, disposable);
	}
	else {
		std::cout << "Account number not found." << std::endl;
	}

}


void TestProgram::withdraw() {

	if (hasNoAccounts()) return;

	printAccounts();

	std::cout << "From which account do you want to withdraw:";
	std::string accountNumber = Input::getString();
	std::cout << "How much do you wish to withdraw: ";
	float amount = Input::getFloat();

	if (bank.withdrawCustomer(accountNumber, amount)) {
		std::cout << "Withdraw successfull." << std::endl;
	}
	else {
		std::cout << "Withdraw failed." << std::endl;
	}

}

void TestProgram::deposit() {

	if (hasNoAccounts()) return;

	printAccounts();

	std::cout << "To which account do you want to deposit:";
	std::string accountNumber = Input::getString();
	std::cout << "How much do you wish to deposit: ";
	float amount = Input::getFloat();

	if (bank.depositCustomer(accountNumber, amount)) {
		std::cout << "Deposit successfull." << std::endl;
	}
	else {
		std::cout << "Account number not found." << std::endl;
	}
}

// Sets the client/customers creditbalance on a specific account.
void TestProgram::credit() {

	if (hasNoAccounts()) return;

	printAccounts();

	std::cout << "to which account do you want to change credit: ";
	std::string accountNumber = Input::getString();
	std::cout << "New credit ";
	float amount = Input::getFloat();

	if (bank.setCustomersCreditBalanace(accountNumber, amount)) {
		std::cout << "Credit changed." << std::endl;
	}
	else {
		std::cout << "Credit could not change." << std::endl;
	}


}

// Create a new account to the customer.
void TestProgram::createAccount() {

	if (bank.createNewCustomerAccount()) {
		std::cout << "Account created." << std::endl;
	}
	else {
		std::cout << "Could not create account." << std::endl;
	}

}

// Removes an account
void TestProgram::removeAccount() {

	if (hasNoAccounts()) return;

	printAccounts();

	std::cout << "Enter the account you want to remove: ";

	if (bank.removeCustomersAccount(Input::getString())) {
		std::cout << "Account removed." << std::endl;
	}
	else {
		std::cout << "Could not remove account.";
	}

}


void TestProgram::printName() const {
	std::cout << "Customer: " + bank.getCustomersName() << std::endl;
}

void TestProgram::printID() const {
	std::cout << "Customer id: " + bank.getCustomersID() << std::endl;
}

void TestProgram::printNrOfAccounts() const {
	std::cout << "Number of accounts: " << bank.getNrOfCustomersAccounts() << std::endl;
}

void TestProgram::printTotalAssets() const {
	std::cout << "Total assets: " << bank.getCustomersTotalAssets() << std::endl;
}

void TestProgram::printAccountInfo( const float balance, const float credit, const float disposable) const {
	std::cout << "Balance: " << balance << std::endl;
	std::cout << "Credit: " << credit << std::endl;
	std::cout << "Disposable: " << disposable << std::endl;
}

// Prints all accounts with its data.
void TestProgram::printSummary() {

	if (hasNoAccounts()) return;

	std::cout << "**** SUMMARY ****" << std::endl;

	std::map<std::string, std::vector<int>> map;
	bank.getCustomersSummary(map);

	for (auto &i : map) {
		std::cout << i.first << std::endl;
		std::vector<int> summary = i.second;
	
		printAccountInfo(summary[0], summary[1], summary[2]);
		std::cout << std::endl;

		
	}
}

// Prints customer/clients account numbers.
void TestProgram::printAccounts() const {

	if (hasNoAccounts()) return;

	std::cout << "Account numbers are: " << std::endl;

	std::vector<std::string> accounts = bank.getCustomersAccountNumbers();
	for (auto &i : accounts)
		std::cout << i << std::endl;
}

// Saves the customers changes and leaves.
void TestProgram::saveAndLeave() {
	bank.changeCustomer();
	std::cout << "Customer saved." << std::endl;
}

// Checks whether a client has 0 accounts.
bool TestProgram::hasNoAccounts() const {
	if (bank.getNrOfCustomersAccounts() == 0) {
		std::cout << "You currently have no accounts." << std::endl;
		return true;
	}

	return false;
}

// clears the screen.
void clearScreen(){

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
	std::cout << "\033[2J\033[1;1H" << std::endl;
#elif _WIN32
	system("cls");
#else
	std::cout << std::string(100, '\n') << std::endl;
#endif 



}