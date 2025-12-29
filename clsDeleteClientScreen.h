
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
	static void ShowDeleteClientScreen()
	{
		_ShowMenuHeader("DELETE CLIENT SCREEN");
		string AccountNumber = "";
		cout << setw(35) << "" << "Enter Account Number : ";
		AccountNumber = clsInputValidation::ReadString();

		while (!clsBankClient::IsExistClient(AccountNumber))
		{
			cout << endl << setw(35) << "" << clsUtil::RED << "Client with this account number is not exist." << endl;
			cout << clsUtil::RESET << setw(35) << "";
			cout << "Enter another one : ";
			AccountNumber = clsInputValidation::ReadString();
		}

		clsBankClient Client = clsBankClient::FindClient(AccountNumber);

		_PrintClient(Client);

		cout << endl << setw(35) << "" << clsUtil::RED << "Are you sure u want to delete this client(Y/N) : ";
		cout << clsUtil::RESET;
		char Answer = 'y';
		cin >> Answer;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (tolower(Answer) == 'y')
		{
			if (Client.Delete())
			{
				cout << endl << setw(40) << "" << clsUtil::GREEN << "Client Deleted Successfully" << endl;
				cout << clsUtil::RESET;
			}
			else
			{

				cout << endl << setw(40) << "" << clsUtil::RED << "There is a prblem with deleting this client." << endl;
				cout << clsUtil::RESET;
			}
		}
	}
};

