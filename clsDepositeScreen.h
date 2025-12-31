#pragma once
#pragma warning (disable : 4267)
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsDepositeScreen : protected clsMenu
{
private:
	static void _PrintClient(clsBankClient client)
	{
		cout << "        CLIENT CARD" << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "FIRST NAME: " << client.FirstName << endl;
		cout << "LAST NAME : " << client.LastName << endl;
		cout << "FULL NAME : " << client.FullName() << endl;
		cout << "EMAIL     : " << client.Email << endl;
		cout << "PHONE     : " << client.Phone << endl;
		cout << "PIN CODE  : " << client.PinCode << endl;
		cout << "Balance   : " << client.Balance << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET;
	}
	static string _ReadAccountNumber()
	{
		cout << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();
		while (!clsBankClient::IsExistClient(AccNumber))// validating client existence
		{
			cout << endl << clsUtil::RED << "Client is not found." << clsUtil::RESET << endl;
			cout << endl << "Enter Account Number: ";
			AccNumber = clsInputValidation::ReadString();
		}
		return AccNumber;
	}

public:
	static void ShowDepositeScreen()
	{
		_ShowMenuHeader("DEPOSIT SCREEN");
		string AccNumber = _ReadAccountNumber();
		clsBankClient client = clsBankClient::FindClient(AccNumber);
		_PrintClient(client);
		cout << endl;
		cout << "Deposit to client " << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "Enter amount to deposit : ";
		float Amount = clsInputValidation::ReadFloatNumber();

		// validating amount > 0
		while (Amount <= 0)
		{
			cout << clsUtil::RED << "Amount must be greater than zero." << clsUtil::RESET << endl;
			cout << "Enter amount to deposit : ";
			Amount = clsInputValidation::ReadFloatNumber();
		}

		cout << clsUtil::RED << "Are you sure you want to deposit " << Amount << " to client " << client.FullName() << " (Y/N)? " << clsUtil::RESET;
		char answer = 'N';
		cin >> answer;

		if (toupper(answer) != 'Y')
		{
			cout << clsUtil::RED << "Operation canceled." << clsUtil::RESET << endl;
			return;
		}


		client.Deposit(Amount);

		switch (client.Save())
		{
			case clsBankClient::enSaveResults::svFailedEmptyobject:
				cout << clsUtil::RED << "Error: Empty client, cannot save." << clsUtil::RESET << endl;
				break;
			case clsBankClient::enSaveResults::svFailedExistObject:
				cout << clsUtil::GREEN << "Amount deposited successfully." << clsUtil::RESET << endl;
				break;
		}

		cout << endl << "Press any key to go back to transaction menu.....";
		_getch();
	}
};

