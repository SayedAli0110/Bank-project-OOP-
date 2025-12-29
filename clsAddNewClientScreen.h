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
		cout << setw(35) << "" << "FIRST NAME: ";
		client.FirstName = clsInputValidation::ReadString();
		cout << setw(35) << "" << "LAST NAME : ";
		client.LastName = clsInputValidation::ReadString();
		cout << setw(35) << "" << "EMAIL     : ";
		client.Email = clsInputValidation::ReadString();
		cout << setw(35) << "" << "PHONE     : ";
		client.Phone = clsInputValidation::ReadString();
		cout << setw(35) << "" << "PIN CODE  : ";
		client.PinCode = clsInputValidation::ReadString();
		cout << setw(35) << "" << "Balance   : ";
		client.Balance = clsInputValidation::ReadFloatNumber();
	}

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

	static void _AddNewClient()
	{
		string AccountNumber = "";
		cout <<setw(35) << "" << "ACCOUNT NUMBER : ";
		AccountNumber = clsInputValidation::ReadString();
		cout << "\n";

		while (clsBankClient::IsExistClient(AccountNumber))
		{
			cout << setw(35)  << "" << clsUtil::RED << "Client with this account number already exists." << clsUtil::RESET<< endl;
			cout << setw(35)  << "" <<  "\nEnter Account number : ";
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
			cout << setw(35) << clsUtil::RED << "" << "Save Faild Because an empty object" << endl;
			break;
		case clsBankClient::svFailedExistObject:
			cout << "\n";
			cout << setw(35) << clsUtil::RED << "" << "Save Faild : client with this number already exists" << endl;
			break;
		case clsBankClient::svSucced:
			_PrintClient(NewClient);
			cout << "\n";
			cout << setw(35) << "" << clsUtil::GREEN << setw(40) << "Client Saved successfuly" << clsUtil::RESET << endl;
		}

	}


public:
	static void ShowAddNewClientScreen()
	{
		_ShowMenuHeader("ADD NEW CLIENT SCREEN");
		_AddNewClient();
	}
};

