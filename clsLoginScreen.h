#pragma once
#define NOMINMAX

#include <iostream>
#include "clsMenu.h"
#include "Global.h"
#include "clsUtil.h"
#include "clsInputValidation.h"
#include "clsBankUser.h"
#include "clsMainMenu.h"

using namespace std;

class clsLoginScreen : clsMenu
{
public:
	static void ShowLoginScreen()
	{
	
		system("cls");

		_ShowMenuHeader("LOGIN SCREEN");

		cout << "Enter Username : ";
		string Username = clsInputValidation::ReadString();

		cout << "Enter Password : ";
		string Password = clsInputValidation::ReadString();

		CurrentUser = clsBankUser::FindUser(Username, Password);

		if (clsBankUser::IsExistUser(CurrentUser.Username))
		{
			cout << "\n\nWelcome Back " << CurrentUser.FullName() << ".....";
			_getch();
			clsMainMenu::ShowMainMenu();
		}
		else
		{
			cout << clsUtil::RED << "\n\nInvalid Username or Password!" << clsUtil::RESET << endl;
			cout << "Try Again...";
			_getch();
		}
	}
};

