#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <iomanip>
#include "clsMenu.h"
#include "clsUtil.h"
#include "clsClientListMenu.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientMenu.h"
#include "clsTransactionsMenu.h"
#include "clsUsersMenuScreen.h"
#include "Global.h"
#include "clsLoginRegistersScreen.h"
#include "clsTransferRegisterScreen.h"

using namespace std;

class clsMainMenu : protected clsMenu
{
private:
	enum enMainMenuOptions
	{
		eListClients = 0,
		eAddNewClient = 1,
		eDeleteClient = 2,
		eUpdateClient = 3,
		eFindClient = 4,
		eTransactionsMenu = 5,
		eShowBalanceSheet = 6,
		eShowLoginRegistersList = 7,
		eShowTransferRegistersList = 8,
		eLogOut = 9
	};

	static void _DisplayListClientsScreen()
	{
		system("cls");
		clsClientListMenu::ShowClientListMenu();
	}

	static void _DisplayAddNewClientScreen()
	{
		system("cls");
		clsUtil::ShowCursor;
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _DisplayDeleteClientScreen()
	{
		system("cls");
		clsUtil::ShowCursor;
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _DisplayUpdateClientScreen()
	{
		system("cls");
		clsUtil::ShowCursor;
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _DisplayFindClientScreen()
	{
		system("cls");
		clsUtil::ShowCursor;
		clsFindClientMenu::ShowFindClientMenu();
	}

	static void _DisplayTransactionsMenuScreen()
	{
		clsTransactionsMenu::ShowTransactionsMenu();
	}

	static void _DisplayUsersMenuScreen()
	{
		clsUsersMenuScreen::ShowUsersMenuScreen();
	}

	static void _DisplayLoginRegistersScreen()
	{
		clsLoginRegistersScreen::ShowLoginRegistersList();
		_GoBackToMainMenu();
	}

	static void _DisplayTransferRegistersScreen()
	{
		clsTransferRegisterScreen::ShowTransferRegistersList();
		_GoBackToMainMenu();
	}

	static void _DisplaylogOutScreen()
	{
		CurrentUser = clsBankUser::GetEmptyUser();
	}

	static void _GoBackToMainMenu()
	{
		cout << "\n" << "Press any key to go back to Main Menu...";
		_getch();

		ShowMainMenu();
	}


	static void _PerformMainMenu(enMainMenuOptions options)
	{
		switch (options)	
		{
		case clsMainMenu::eListClients:
			_DisplayListClientsScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eAddNewClient:
			_DisplayAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eDeleteClient:
			_DisplayDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eUpdateClient:
			_DisplayUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eFindClient:
			_DisplayFindClientScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eTransactionsMenu:
			_DisplayTransactionsMenuScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eShowBalanceSheet:
			_DisplayUsersMenuScreen();
			_GoBackToMainMenu();
			break;
		case clsMainMenu::eShowLoginRegistersList:
			_DisplayLoginRegistersScreen();
			break;
		case clsMainMenu::eShowTransferRegistersList:
			_DisplayTransferRegistersScreen();
			break;
		case clsMainMenu::eLogOut:
			_DisplaylogOutScreen();
			break;
		default:
			break;
		}
	}
	
	static void _PrintHeader()
	{
		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=') << clsUtil::RESET << endl;

		cout << setw(50) << "" << "Main Menu" << endl;

		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=') << clsUtil::RESET << endl;
	}

public:

	static void ShowMainMenu()
	{
		system("cls");

		_ShowMenuHeader("MAIN MENU SCREEN");
		vector<string> MainMenuOptions = {
			"1  - List Clients",
			"2  - Add New Client",
			"3  - Delete Client",
			"4  - Update Client",
			"5  - Find Client",
			"6  - Transactions Menu",
			"7  - Manage Users Menu",
			"8  - Login Registers",
			"9  - Transfer Registers",
			"10 - Logout"
		};
		_PrintHeader();
		_PerformMainMenu((enMainMenuOptions)_PerformMenuOptions(MainMenuOptions,10));
	}

};
