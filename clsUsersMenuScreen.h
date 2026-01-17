#pragma once
#pragma warning(disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsMenu.h"
#include "clsAddUserScreen.h"
#include "clsUserListScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"

using namespace std;


class clsUsersMenuScreen : protected clsMenu
{
private:
	enum enUsersMenuOptions
	{
		eShowUsersList = 0,
		eFindUser = 1,
		eAddNewUser = 2,
		eDeleteUser = 3,
		eUpdateUserInfo = 4,
		eMainMenu = 5
	};
	static void _GoBackToUsersMenuScreen()
	{
		cout << "\n\nPress any key to go back to Users Menu Screen...";
		_getch();
		ShowUsersMenuScreen();
	}

	static void _ShowUserListScreen()
	{
		system("cls");
		clsUserListScreen::ShowUserListScreen();
	}

	static void _FindUserScreen()
	{
		system("cls");
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _AddNewUserScreen()
	{
		system("cls");
		clsAddUserScreen::AddNewUser();
	}

	static void _DeleteUserScreen()
	{
		system("cls");
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _UpdateUserInfoScreen()
	{
		system("cls");
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _PrintSubHeader(string title)
	{
		cout << setw(35) << "" <<  clsUtil::YELLOW <<string(40, '-') << clsUtil::RESET << endl;

		cout << setw(45) << "" << title << endl;

		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '-') << clsUtil::RESET << endl;

	}

	

	
public:
	static void ShowUsersMenuScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsBankUser::enPermissions::eManageUsers))
		{
			return;
		}

		vector<string> options = { "1- Show Users List", "2- Find User", "3- Add New User", "4- Delete User", "5- Update User Info", "6- Main Menu" };


		_ShowMenuHeader("Users Menu Screen");
		_PrintSubHeader("Users Menu");

		short selectedOption = _PerformMenuOptions(options, 10 );

		switch (selectedOption)
		{
		case enUsersMenuOptions::eShowUsersList:
			_ShowUserListScreen();
			_GoBackToUsersMenuScreen();
			break;
		case enUsersMenuOptions::eFindUser:
			_FindUserScreen();
			_GoBackToUsersMenuScreen();
			break;
		case enUsersMenuOptions::eAddNewUser:
			_AddNewUserScreen();
			_GoBackToUsersMenuScreen();
			break;
		case enUsersMenuOptions::eDeleteUser:
			_DeleteUserScreen();
			_GoBackToUsersMenuScreen();
			break;
		case enUsersMenuOptions::eUpdateUserInfo:
			_UpdateUserInfoScreen();
			_GoBackToUsersMenuScreen();
			break;
		case enUsersMenuOptions::eMainMenu:
			return;
		}
	}

};

