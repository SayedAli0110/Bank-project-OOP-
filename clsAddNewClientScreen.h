#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include <iomanip>

using namespace std;

class clsAddNewClientScreen : protected clsMenu
{
private:
	static void _ReadClient(clsBankClient& client)
	{
		cout << "FIRST NAME: ";
		client.FirstName = clsInputValidation::ReadString();
		cout << "LAST NAME : ";
		client.LastName = clsInputValidation::ReadString();
		cout << "EMAIL     : ";
		client.Email = clsInputValidation::ReadString();
		cout << "PHONE     : ";
		client.Phone = clsInputValidation::ReadString();
		cout << "PIN CODE  : ";
		client.PinCode = clsInputValidation::ReadString();
		cout << "Balance   : ";
		client.Balance = clsInputValidation::ReadFloatNumber();
	}

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

	static void _AddNewClient()
	{
		string AccountNumber = "";
		cout << "ACCOUNT NUMBER : ";
		AccountNumber = clsInputValidation::ReadString();
		cout << "\n";

		while (clsBankClient::IsExistClient(AccountNumber))
		{
			cout << clsUtil::RED << "Client with this account number already exists." << clsUtil::RESET<< endl;
			cout <<  "\nEnter Account number : ";
			AccountNumber = clsInputValidation::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);
		_ReadClient(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFailedEmptyobject:
			cout << "\n";
			cout << clsUtil::RED << "Save Faild Because an empty object" << endl;
			break;
		case clsBankClient::svFailedExistObject:
			cout << "\n";
			cout << clsUtil::RED << "Save Faild : client with this number already exists" << endl;
			break;
		case clsBankClient::svSucced:
			_PrintClient(NewClient);
			cout << "\n";
			cout << clsUtil::GREEN << "Client Saved successfuly" << clsUtil::RESET << endl;
		}

	}


public:
	static void ShowAddNewClientScreen()
	{
		_ShowMenuHeader("ADD NEW CLIENT SCREEN");
		_AddNewClient();
	}
};

