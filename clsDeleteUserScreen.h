#pragma once
#define NOMINMAX

#include <iostream>
#include "clsUtil.h"
#include "clsMenu.h"
#include "clsBankUser.h"
#include "clsInputValidation.h"

using namespace std;

class clsDeleteUserScreen : protected clsMenu
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

public:
	static void ShowDeleteUserScreen()
	{
		_ShowMenuHeader("DELETE USER SCREEN");
		
		cout << "Enter Username : ";
		string UserName = clsInputValidation::ReadString();

		while (!clsBankUser::IsExistUser(UserName))
		{
			cout << clsUtil::RED << "User with this username does not exist." << clsUtil::RESET << endl;
			cout << "\nEnter Username : ";
			UserName = clsInputValidation::ReadString();
		}

		clsBankUser User = clsBankUser::FindUser(UserName);

		cout << endl;
		_PrintUser(User);

		cout << "\nAre you sure you want to delete this user? (Y/N): ";
		char confirmation = 'n';
		cin >> confirmation;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (confirmation == 'Y' || confirmation == 'y')
		{
			if(User.Delete())
				cout << clsUtil::GREEN << "\nUser deleted successfully." << clsUtil::RESET << endl;
			else
				cout << clsUtil::RED << "\nFailed to delete user." << clsUtil::RESET << endl;
		}
		else
		{
			cout << clsUtil::YELLOW << "\nUser deletion canceled." << clsUtil::RESET << endl;
		}

	}
};

