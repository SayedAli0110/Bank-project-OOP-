#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsMenu.h"
#include "clsInputValidation.h"
#include "clsUtil.h"
#include "Global.h"

using namespace std;

class clsTransferScreen : protected clsMenu
{
	static void _PrintNeededClientInfo(clsBankClient Client)
	{
		cout << clsUtil::YELLOW	<<"------------------------------------------" << clsUtil::RESET<< endl;
		cout << "Name           : " << Client.FullName() << endl;
		cout << "Account Number : " << Client.AccountNumber() << endl;
		cout << "Balance        : " << to_string(Client.Balance) << endl;
		cout << clsUtil::YELLOW << "------------------------------------------" << clsUtil::RESET << endl;
	}
	
public:

	static void ShowTransferScreen()
	{
		system("cls");

		_ShowMenuHeader("TRANSFER SCREEN");
		
		string FromAccountNumber = "";
		string ToAccountNumber = "";
		float Amount = 0;

		cout << "From (Account Number) : ";
		FromAccountNumber = clsInputValidation::ReadString();

		clsBankClient FromClient = clsBankClient::FindClient(FromAccountNumber);

		while (FromClient.IsEmpty())
		{
			cout << clsUtil::RED << "There Is no such a Client with this account number"  << clsUtil::RESET << endl;

			cout << "From (Account Number) : ";
			FromAccountNumber = clsInputValidation::ReadString();

			FromClient = clsBankClient::FindClient(FromAccountNumber);

			
		}

		cout << clsUtil::GREEN << "Client is found successfully" << clsUtil::RESET << endl;
		_PrintNeededClientInfo(FromClient);

		cout << "\nTo   (Account Number) : ";
		ToAccountNumber = clsInputValidation::ReadString();

		clsBankClient ToClient = clsBankClient::FindClient(ToAccountNumber);

		while (ToClient.IsEmpty())
		{
			cout << clsUtil::RED << "There Is no such a Client with this account number" << clsUtil::RESET << endl;

			cout << "to   (Account Number) : ";
			ToAccountNumber = clsInputValidation::ReadString();

		    ToClient = clsBankClient::FindClient(ToAccountNumber);
		}
		
		cout << clsUtil::GREEN << "Client is found successfully" << clsUtil::RESET << endl;
		_PrintNeededClientInfo(ToClient);

		cout << "\nAmount of mony         : ";
		Amount = clsInputValidation::ReadFloatNumber();

		while (!FromClient.Withdraw(Amount))
		{
			cout << clsUtil::RED << "Enterd amount is greater than the client balance" << clsUtil::RESET << endl;
			cout << "Amount of mony        : ";
			Amount = clsInputValidation::ReadFloatNumber();
		}

		char SureToDo = 'n';

		cout << clsUtil::RED << "Are you sure you want to perform this process(y/n)? : " << clsUtil::RESET;
		cin >> SureToDo;

		
		if (tolower(SureToDo) == 'y')
		{
			ToClient.Deposit(Amount);
			cout << clsUtil::GREEN << "The process is done successfully :)" << clsUtil::RESET << endl;

			CurrentUser.TransferRegister(FromClient, ToClient, Amount);
		}
		else
		{
			cout << clsUtil::RED << "Faild to Done the proccess " << clsUtil::RESET << endl;
		}

		cout << endl << "Press any key to go back to transaction menu.....";
		_getch();
	}

};

