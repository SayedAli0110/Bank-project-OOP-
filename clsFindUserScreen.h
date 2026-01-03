#pragma once

#include <iostream>
#include "clsMenu.h"
#include "clsInputValidation.h"
#include "clsUtil.h"
#include "clsBankUser.h"

using namespace std;

class clsFindUserScreen : protected clsMenu
{
private:
	static void _PrintUser(clsBankUser User)
	{
		cout << "        USER CARD" << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "FIRST NAME: " << User.FirstName << endl;
		cout << "LAST NAME : " << User.LastName << endl;
		cout << "FULL NAME : " << User.FullName() << endl;
		cout << "EMAIL     : " << User.Email << endl;
		cout << "PHONE     : " << User.Phone << endl;
		cout << "PASSWORD  : " << User.Password << endl;
		cout << "PERMISSIONS : " << User.Permissions << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET;
	}

	static string _GetUserNameToSearch()
	{
		cout << "ENTER USERNAME: ";
		return clsInputValidation::ReadString();
	}

public:
	static void ShowFindUserScreen()
	{
		_ShowMenuHeader("FIND USER SCREEN");

		string UserName = _GetUserNameToSearch();

		while (!clsBankUser::IsExistUser(UserName))
		{
			cout << clsUtil::RED <<  "\nUSER NOT FOUND, PLEASE TRY AGAIN.\n" << clsUtil::RESET;
			UserName = _GetUserNameToSearch();
		}


		clsBankUser User = clsBankUser::FindUser(UserName);

		if (clsBankUser::IsExistUser(User.Username))
		{
			cout << clsUtil::GREEN << "\nUSER FOUND SUCCESSFULLY.\n" << clsUtil::RESET;
			_PrintUser(User);
		}
		
	}
};

