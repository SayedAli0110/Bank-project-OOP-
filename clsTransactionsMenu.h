#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include "clsMenu.h"
#include "clsUtil.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"

using namespace std;

class clsTransactionsMenu : protected clsMenu
{
private:
	enum enTransactionsOptions
	{
		eDeposit = 0,
		eWithdraw = 1,
		eTotalBalances = 2,
		eExit = 3
	};

	static void _DisplayDepositScreen()
	{
		system("cls");
		clsDepositeScreen::ShowDepositeScreen();
	}

	static void _DisplayWithdrawScreen()
	{
		system("cls");
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _DisplayTotalBalancesScreen()
	{
		system("cls");

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		string subTitle = to_string(vClients.size()) + " Client/s";
		float Balance = clsBankClient::GetTotalBalance(vClients);

		_ShowMenuHeader("TOTAL BALANCES SCREEN",subTitle);


		cout << setw(20) << "" << clsUtil::YELLOW << "-----------------------------------------------------------------" << clsUtil::RESET << endl;

		cout << setw(20) << "" << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "ACCOUNT NUMBER";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "CLIENT NAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << "BALANCE" << endl;
		cout << setw(20) << "" << clsUtil::YELLOW << "-----------------------------------------------------------------" << clsUtil::RESET << endl;

		if (vClients.empty())
		{
			cout << setw(20) << "" << clsUtil::RED << "THERE IS NO CLIENTS TO SHOW THEIR BALANCE." << clsUtil::RESET << endl;
		}
		else
		{
			for (size_t i = 0; i < vClients.size(); i++)
			{
				cout << setw(20) << "" << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << vClients.at(i).AccountNumber();
				cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << vClients.at(i).FullName();
				cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << to_string(vClients.at(i).Balance) << endl;
			}
		}

		cout << setw(20) << "" << clsUtil::YELLOW << "-----------------------------------------------------------------" << clsUtil::RESET << endl;
		cout << setw(20) << "" << clsUtil::RED << "TOTAL BALANCE : " << clsUtil::RESET << Balance << endl;
		cout << setw(20) << "" << clsUtil::RED << "IN WORDS      : " << clsUtil::RESET << clsUtil::NumberToText((int)Balance) << endl;
		cout << setw(20) << "" << clsUtil::YELLOW << "-----------------------------------------------------------------" << clsUtil::RESET << endl;

		cout << endl << "Press any key to back to transactions menu....";
		_getch();
	}

	static void _PerformTransactionsMenu(enTransactionsOptions options)
	{
		switch (options)
		{
		case clsTransactionsMenu::eDeposit:
			_DisplayDepositScreen();
			ShowTransactionsMenu();
			break;
		case clsTransactionsMenu::eWithdraw:
			_DisplayWithdrawScreen();
			ShowTransactionsMenu();
			break;
		case clsTransactionsMenu::eTotalBalances:
			_DisplayTotalBalancesScreen();
			ShowTransactionsMenu();
			break;
		case clsTransactionsMenu::eExit:
			break;
		}
	}

	static void _PrintSubHeader(string title)
	{
		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '-') << clsUtil::RESET << endl;

		cout << setw(45) << "" << title << endl;

		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '-') << clsUtil::RESET << endl;

	}


public:
	static void ShowTransactionsMenu()
	{
		system("cls");

		_ShowMenuHeader("TRANSACTIONS MENU SCREEN");
		_PrintSubHeader("Transactions Menu");
		vector<string> TransOptions = {
			"1- Deposit",
			"2- Withdraw",
			"3- Total Balances",
			"4- Exit"
		};

		// Use same option selection method / start line as main menu
		_PerformTransactionsMenu((enTransactionsOptions)_PerformMenuOptions(TransOptions, 8));
	}
};