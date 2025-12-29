#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsFindClientMenu : protected clsMenu
{
protected:
	static void _PrintClient(clsBankClient client)
	{
		cout << setw(35) << "" << "        CLIENT CARD" << endl;
		cout << setw(35) << "" << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << setw(35) << "" << "FIRST NAME: " << client.FirstName << endl;
		cout << setw(35) << "" << "LAST NAME : " << client.LastName << endl;
		cout << setw(35) << "" << "FULL NAME : " << client.FullName() << endl;
		cout << setw(35) << "" << "EMAIL     : " << client.Email << endl;
		cout << setw(35) << "" << "PHONE     : " << client.Phone << endl;
		cout << setw(35) << "" << "PIN CODE  : " << client.PinCode << endl;
		cout << setw(35) << "" << "Balance   : " << client.Balance << endl;
		cout << setw(35) << "" << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET;
	}

public:
	static void ShowFindClientMenu()
	{
		_ShowMenuHeader("FIND CLIENT MENU", "SEARCH BY ACCOUNT NUMBER");
		cout << setw(35) << "" << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();

		// validating client existence
		while (!clsBankClient::IsExistClient(AccNumber))
		{
			cout << setw(35) << "" << clsUtil:: RED << "Client not found " << clsUtil:: RESET<< endl;
			cout << setw(35) << "" << "Enter Account Number : ";
			AccNumber = clsInputValidation::ReadString();
		}

		clsBankClient client = clsBankClient::FindClient(AccNumber);

		cout << endl;
		cout << setw(35) << "" << clsUtil::GREEN<< "Client Found Successfully!" << clsUtil::RESET<< endl << endl;

		_PrintClient(client);

	}
};

