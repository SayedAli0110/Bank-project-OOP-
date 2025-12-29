#pragma once 
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsUpdateClientScreen : protected clsMenu
{
protected:
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

public:
	static void ShowUpdateClientScreen()
	{
		_ShowMenuHeader("UPDATE CLIENT SCREEN");
		cout << setw(35) << "" << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();
		while (!clsBankClient::IsExistClient(AccNumber))// validating client existence
		{
			cout << setw(35) << "" << clsUtil::RED << "Client not found." << clsUtil::RESET << endl;
			cout << setw(35) << "" << "Enter Account Number: ";
			AccNumber = clsInputValidation::ReadString();
		}
		clsBankClient client = clsBankClient::FindClient(AccNumber);
		_PrintClient(client);
		cout << endl;
		cout << setw(55) << "Update client " << endl;
		cout << setw(40) << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET<< endl;
		_ReadClient(client);

		client.Save();

		cout << setw(50) << "press any button to continue...." << endl;
		_getch();

	}

};

