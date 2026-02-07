#define NOMINMAX
#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "clsBankUser.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsUpdateUserScreen : protected clsMenu
{
private:
	static void _ReadUser(clsBankUser& user)
	{
		cout  << "FIRST NAME : ";
		user.FirstName = clsInputValidation::ReadString();
		cout  << "LAST NAME  : ";
		user.LastName = clsInputValidation::ReadString();
		cout  << "EMAIL      : ";
		user.Email = clsInputValidation::ReadString();
		cout  << "PHONE      : ";
		user.Phone = clsInputValidation::ReadString();
		cout  << "PASSWORD   : ";
		user.Password = clsInputValidation::ReadString();
		cout  << "PERMISSIONS: ";
		// Read as string then convert to short to avoid depending on unknown ReadNumber API
		string perms = clsInputValidation::ReadString();
		user.Permissions = (short)stoi(perms);
	}

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

		cout << "\nDo you want to give access to show Transfer registers(y/n)";
		cin >> answer;

		if (tolower(answer) == 'y')
		{
			User.Permissions += clsBankUser::enPermissions::eShowTransferRegisters;
		}

	}

	static void _PrintUser(clsBankUser user)
	{
		cout << "         USER CARD" << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "FIRST NAME : " << user.FirstName << endl;
		cout << "LAST NAME  : " << user.LastName << endl;
		cout << "FULL NAME  : " << user.FullName() << endl;
		cout << "EMAIL      : " << user.Email << endl;
		cout << "PHONE      : " << user.Phone << endl;
		cout << "USERNAME   : " << user.Username << endl;
		cout << "PASSWORD   : " << user.Password << endl;
		cout << "PERMISSIONS: " << user.Permissions << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET;
	}

	static void _UpdateUserName(clsBankUser& user)
	{
		cout << "Enter New First Name: ";
		user.FirstName = clsInputValidation::ReadString();
		cout << "Enter New Last Name: ";
		user.LastName = clsInputValidation::ReadString();
	}

	static void _UpdateUserEmail(clsBankUser& user)
	{
		cout << "Enter New Email: ";
		user.Email = clsInputValidation::ReadString();
	}

	static void _UpdateUserPhone(clsBankUser& user)
	{
		cout << "Enter New Phone: ";
		user.Phone = clsInputValidation::ReadString();
	}

	static void _UpdateUserPassword(clsBankUser& user)
	{
		cout << "Enter New Password: ";
		user.Password = clsInputValidation::ReadString();
	}

	static void _UpdateUserPermissions(clsBankUser& user)
	{
		cout << "Enter New Permissions: ";
		
		_ReadPermissions(user);
	}

public:
	static void ShowUpdateUserScreen()
	{

		if (!CheckAccessRights(clsBankUser::enPermissions::eManageUsers))
		{
			return;
		}

		_ShowMenuHeader("UPDATE USER SCREEN");

		short CurrentLine = 8;

		cout << "Enter Username : ";
		string Username = clsInputValidation::ReadString();
		while (!clsBankUser::IsExistUser(Username)) // validating user existence
		{
			system("cls");
			_ShowMenuHeader("UPDATE USER SCREEN", "User not found");
			cout << "Enter Username: ";
			Username = clsInputValidation::ReadString();
		}

		clsBankUser User = clsBankUser::FindUser(Username);

		while (User.Username == CurrentUser.Username)
		{
			system("cls");
			_ShowMenuHeader("UPDATE USER SCREEN", "You cannot update your own user.");
			cout << "\nEnter Username : ";
			Username = clsInputValidation::ReadString();
			while (!clsBankUser::IsExistUser(Username))
			{
				system("cls");
				_ShowMenuHeader("UPDATE USER SCREEN", "User not found");
				cout << "\nEnter Username : ";
				Username = clsInputValidation::ReadString();
			}

			User = clsBankUser::FindUser(Username);
		}

		clsBankUser user = clsBankUser::FindUser(Username);

		vector<string> vTargetUpdateItem =
		{
		  "1-Name",
		  "2-Email",
		  "3-Phone",
		  "4-Password",
		  "5-Permissions",
		  "6-All",
		  "7-Exit"
		};

		enum enUpdateMenuOptions
		{
			eUpdateName = 0,
			eUpdateEmail = 1,
			eUpdatePhone = 2,
			eUpdatePassword = 3,
			eUpdatePermissions = 4,
			eUpdateAll = 5,
			eExit = 6
		};

		clsUtil::MoveCursorTo(0, CurrentLine-1);
		cout << setw(35) << "" << endl;
		cout << setw(35) << "" << "Choose what do you want to update for this user?" << endl;
		CurrentLine++;
		short SelectedItem;

		SelectedItem = _PerformMenuOptions(vTargetUpdateItem, CurrentLine);
		switch (SelectedItem)
		{
		case enUpdateMenuOptions::eUpdateName:
			_UpdateUserName(user);
			break;
		case enUpdateMenuOptions::eUpdateEmail:
			_UpdateUserEmail(user);
			break;
		case enUpdateMenuOptions::eUpdatePhone:
			_UpdateUserPhone(user);
			break;
		case enUpdateMenuOptions::eUpdatePassword:
			_UpdateUserPassword(user);
			break;
		case enUpdateMenuOptions::eUpdatePermissions:
			_UpdateUserPermissions(user);
			break;
		case enUpdateMenuOptions::eUpdateAll:
			_ReadUser(user);
			break;

		default:
			break;
		}

		switch (user.Save())
		{
		case clsBankUser::enSaveResults::svFaildEmptyObject:
			cout << clsUtil::RED << "Update Failed Because the empty object." << clsUtil::RESET << endl;
			break;
		case clsBankUser::enSaveResults::svSucceedUpdateUser:
			cout << clsUtil::GREEN << "User Updated successfully" << clsUtil::RESET << endl;
			break;
		}
		cout << "----------------------------------------" << endl;
		
	}

};

