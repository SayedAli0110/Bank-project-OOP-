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
	static void _ReadPermissions(clsBankUser& User)
	{
		char answer = 'n';

		cout << "\nDo you want to give full access(y/n): ";
		cin >> answer;
		
		if (tolower(answer) == 'y')
		{
			User.Permissions = clsBankUser::enPermissions::eAdmin;
			return;
		}

		cout << "\nDo you want to give show clients list access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eShowClenttsList;
		}

		cout << "\nDo you want to give add new client access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eAddNewClient;
		}

		cout << "\nDo you want to give delete client access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eDeleteClient;
		}

		cout << "\nDo you want to give update client access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eUpdateClient;
		}

		cout << "\nDo you want to give find client access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eFindClient;
		}

		cout << "\nDo you want to give show transactions menu access(y/n): ";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eTransactions;
		}

		cout << "\nDo you want to give access to manage users(y/n)";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eManageUsers;
		}

	}
	static void _ReadUser(clsBankUser& User)
	{
		cout << "FIRST NAME  : ";
		User.FirstName = clsInputValidation::ReadString();
		cout << "LAST NAME   : ";
		User.LastName = clsInputValidation::ReadString();
		cout << "EMAIL       : ";
		User.Email = clsInputValidation::ReadString();
		cout << "PHONE       : ";
		User.Phone = clsInputValidation::ReadString();
		cout << "PASSWORD    : ";
		User.Password = clsInputValidation::ReadString();
		cout << "PERMISSIONS : " << endl;
		_ReadPermissions(User);
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
		clsMenu::_ShowMenuHeader("ADD USER SCREEN");

		string Username = ReadUsername();

		while (clsBankUser::IsExistUser(Username))
		{
			cout << clsUtil::RED << "User with this username already exists." << clsUtil::RESET << endl;
			cout << "\nEnter Username : ";
			Username = clsInputValidation::ReadString();
		}

		clsBankUser NewUser = clsBankUser::GetAddNewUser(Username);

		_ReadUser(NewUser);

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

