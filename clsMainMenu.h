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
		eLogOut = 7
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
		cout << clsUtil::RemoveCursor;

		_ShowMenuHeader("MAIN MENU SCREEN");
		vector<string> MainMenuOptions = {
			"1- List Clients",
			"2- Add New Client",
			"3- Delete Client",
			"4- Update Client",
			"5- Find Client",
			"6- Transactions Menu",
			"7- Manage Users Menu",
			"8- Log Out"
		};
		_PrintHeader();
		_PerformMainMenu((enMainMenuOptions)_PerformMenuOptions(MainMenuOptions,8));
	}

};

	static short _PerformMenuOptions(vector<string> options , short StartLine = 0)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    short selected = 0;
    short pos = StartLine;
    COORD coord = { 40 , pos };
    while (true)
    {
        // make sure any pending output is written before moving the cursor
        cout.flush();

        // clear screen region start and reprint options from the correct place
        SetConsoleCursorPosition(hConsole, { 40,0 });
        pos = StartLine;

        // higlight selected option
        for (int i = 0; i < options.size(); i++)
        {
            if (i == selected)
            {
                coord = { 44, pos};
                SetConsoleCursorPosition(hConsole, coord);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << options[i] << "\n";
            }
            else
            {
                coord = { 44, pos };
                SetConsoleCursorPosition(hConsole, coord);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << options[i] << "\n";
            }
            pos++;
        }

        // print separator using Win32 attributes (avoid emitting ANSI codes here)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // yellow-ish
        cout << setw(40) << string(40, '-') << endl;

        // reset to default color so future output is consistent
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        // handle input
        char ch = _getch();
        if (ch == 0 || ch == -32) //arrow keys
        {
            switch (ch = _getch())
            {
            case 72: // up arrow
                if (selected == 0) selected = options.size() - 1;
                else selected--;
                break;
            case 80: // down arrow
                if (selected == options.size() - 1) selected = 0;
                else selected++;
                break;
            }
        }
        else if (ch == 13) // enter key 
        {
            return selected;
        }
    }
}
