
#pragma once

#include <iostream>
#include "clsMenu.h"
#include "clsBankClient.h"
#include <iomanip>
#include <vector>
#include "clsInputValidation.h"
#include <limits>
#include <cctype>

using namespace std;

class clsDeleteClientScreen : protected clsMenu
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

public:
	static void ShowDeleteClientScreen()
	{

		if (!CheckAccessRights(clsBankUser::enPermissions::eDeleteClient))
		{
			return;
		}

		_ShowMenuHeader("DELETE CLIENT SCREEN");
		string AccountNumber = "";
		cout << "Enter Account Number : ";
		AccountNumber = clsInputValidation::ReadString();

		while (!clsBankClient::IsExistClient(AccountNumber))
		{
			system("cls");
			_ShowMenuHeader("DELETE CLIENT SCREEN", "Client not found");
			cout << clsUtil::RESET;
			cout << "Enter another one : ";
			AccountNumber = clsInputValidation::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);

		_PrintClient(Client);

		cout << endl << clsUtil::RED << "Are you sure u want to delete this client(Y/N) : ";
		cout << clsUtil::RESET;
		char Answer = 'y';
		cin >> Answer;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (tolower(Answer) == 'y')
		{
			if (Client.Delete())
			{
				cout << clsUtil::GREEN << "Client Deleted Successfully" << endl;
				cout << clsUtil::RESET;
			}
			else
			{

				cout << endl << clsUtil::RED << "There is a prblem with deleting this client." << endl;
				cout << clsUtil::RESET;
			}
		}
	}
};

