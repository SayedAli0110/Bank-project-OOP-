#define NOMINMAX
#pragma once
#include <iostream>
#include "clsUtil.h"
#include "clsMenu.h"
#include "clsBankUser.h"
#include "clsInputValidation.h"

using namespace std;

class clsUpdateUserScreen : protected clsMenu
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

		cout << "\nDo you want to give access to show login registers(y/n)";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eShowLoginRegisters;
		}

	}

	static string _GetUserNameToUpdate()
	{
		cout << "ENTER USERNAME: ";
		return clsInputValidation::ReadString();
	}

	static void _PrintUser(clsBankUser& User)
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

	static clsBankUser _ReadUserInfo(clsBankUser& User)
	{
		cout << "\nENTER FIRST NAME: ";
		User.FirstName = clsInputValidation::ReadString();
		cout << "ENTER LAST NAME: ";
		User.LastName = clsInputValidation::ReadString();
		cout << "ENTER EMAIL: ";
		User.Email = clsInputValidation::ReadString();
		cout << "ENTER PHONE: ";
		User.Phone = clsInputValidation::ReadString();
		cout << "ENTER PASSWORD: ";
		User.Password = clsInputValidation::ReadString();
		cout << "ENTER PERMISSIONS: " << endl;

		_ReadPermissions(User);

		return User;
	}

public:
	static void ShowUpdateUserScreen()
	{
		_ShowMenuHeader("UPDATE USER SCREEN");

		string UserName = _GetUserNameToUpdate();

		while (!clsBankUser::IsExistUser(UserName))
		{
			cout << clsUtil::RED << "\nUSER NOT FOUND, PLEASE TRY AGAIN.\n" << clsUtil::RESET;
			UserName = _GetUserNameToUpdate();
		}
		
		clsBankUser User = clsBankUser::FindUser(UserName);

		_PrintUser(User);

		cout << endl << "Are you sure you want to update this user? (Y/N): ";
		char answer = 'n';
		cin >> answer;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (toupper(answer) == 'Y')
		{
			User = clsBankUser::GetEmptyUser();

			User.Username = UserName;

			_ReadUserInfo(User);

			User.Update();

			switch (User.Save())
			{
			case clsBankUser::enSaveResults::svSucceedUpdateUser:
				cout << clsUtil::GREEN << "\nUSER UPDATED SUCCESSFULLY.\n" << clsUtil::RESET;
				_PrintUser(User);
				break;
			case clsBankUser::enSaveResults::svFaildEmptyObject:
				cout << clsUtil::RED << "\nERROR: EMPTY USER OBJECT.\n" << clsUtil::RESET;
				break;
			}
		}
		else
		{
			cout << clsUtil::YELLOW << "\nUPDATE OPERATION CANCELLED.\n" << clsUtil::RESET;
		}
	}
};

