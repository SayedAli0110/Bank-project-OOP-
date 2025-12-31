#pragma once
#pragma warning (disable : 4267)
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsWithdrawScreen : protected clsMenu
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
			cout << endl <<"Enter Account Number: ";
			AccNumber = clsInputValidation::ReadString();
		}
		return AccNumber;
	}

public:
	static void ShowWithdrawScreen()
	{
		_ShowMenuHeader("WITHDRAW SCREEN");

		string Accnum = _ReadAccountNumber();

		clsBankClient client = clsBankClient::FindClient(Accnum);
		
		_PrintClient(client);
		cout << endl;

		cout << "Withdraw from Client " << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "Enter an amount to withdraw (multiplyes of 5): ";

		float Amount = clsInputValidation::ReadFloatNumber();

		while (((int)Amount % 5) != 0)
		{
			cout << endl << clsUtil::RED << "You've entered a denied amount of money" << clsUtil::RESET << endl;
			cout << "Enter an amount to withdraw (multiplyes of 5): ";
			Amount = clsInputValidation::ReadFloatNumber();
		}

		if (client.Withdraw(Amount))
		{
			cout << endl << clsUtil::GREEN << "Amount withdrawn successfully." << clsUtil::RESET << endl;
			cout << "New balance is: " << client.Balance << endl;
		}
		else
		{
			cout << endl << clsUtil::RED << "Failed to withdraw the amount." << clsUtil::RESET << endl;
			cout << "Insufficient balance." << endl;
		}

		cout << endl <<"Press any key to go back to transaction menu.....";
		_getch();
	}
};

