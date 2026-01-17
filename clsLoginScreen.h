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
private:
	static void _LockLoginprogress()
	{
		system("cls");
		clsMenu::_ShowMenuHeader("LOGIN FAILD", "\b\b\bif you have any issue contact the IT");
		_getch();
		exit(0);
	}

public:
	static void ShowLoginScreen()
	{

		short trials = 3;
		
		string subtitle = "";

		do
		{
			system("cls");
			_ShowMenuHeader("LOGIN SCREEN", subtitle);
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
				trials--;

				string ErorMesage = "incorrect Username/passowrd\n\t\t\t\t\tyou have " + to_string(trials);
				ErorMesage += " times remaining";

				subtitle = ErorMesage;
			}

		} while (trials > 0);

		_LockLoginprogress();
	}
};

