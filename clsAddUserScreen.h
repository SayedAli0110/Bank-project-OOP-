#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsBankUser.h"
#include "clsMenu.h"
#include "clsInputValidation.h"

using namespace std;

class clsAddUserScreen : protected clsMenu
{
private:
	static void _ReadUser(clsBankUser& User)
	{
		cout << "FIRST NAME: ";
		User.FirstName = clsInputValidation::ReadString();
		cout << "LAST NAME : ";
		User.LastName = clsInputValidation::ReadString();
		cout << "EMAIL     : ";
		User.Email = clsInputValidation::ReadString();
		cout << "PHONE     : ";
		User.Phone = clsInputValidation::ReadString();
		cout << "PASSWORD  : ";
		User.Password = clsInputValidation::ReadString();
	}

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

	static string ReadUsername()
	{
		cout << "USERNAME  : ";
		string Username = clsInputValidation::ReadString();
		return Username;
	}

public:
	static void AddNewUser()
	{
		string Username = ReadUsername();

		while (clsBankUser::IsExistUser(Username))
		{
			cout << clsUtil::RED << "User with this username already exists." << clsUtil::RESET << endl;
			cout << "\nEnter Username : ";
			Username = clsInputValidation::ReadString();
		}

		clsBankUser NewUser = clsBankUser::GetAddNewUser(Username);

		_ReadUser(NewUser);
		short permissions = 0;

		switch (NewUser.Save())
		{

		case clsBankUser::enSaveResults::svSucceedAddNewUser:
			cout << clsUtil::GREEN << "\nUser Added Successfully." << clsUtil::RESET << endl;
			_PrintUser(NewUser);
			break;

		case clsBankUser::enSaveResults::svFaildEmptyObject:
			cout << clsUtil::RED << "\nCannot Save an empty object" << clsUtil::RESET << endl;
			break;
		}
	}
};

