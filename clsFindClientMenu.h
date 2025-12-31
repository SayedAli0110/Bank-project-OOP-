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

public:
	static void ShowFindClientMenu()
	{
		_ShowMenuHeader("FIND CLIENT MENU", "SEARCH BY ACCOUNT NUMBER");
		cout << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();

		// validating client existence
		while (!clsBankClient::IsExistClient(AccNumber))
		{
			cout << clsUtil:: RED << "Client not found " << clsUtil:: RESET<< endl;
			cout << "Enter Account Number : ";
			AccNumber = clsInputValidation::ReadString();
		}

		clsBankClient client = clsBankClient::FindClient(AccNumber);

		cout << endl;
		cout << clsUtil::GREEN<< "Client Found Successfully!" << clsUtil::RESET<< endl << endl;

		_PrintClient(client);

	}
};

