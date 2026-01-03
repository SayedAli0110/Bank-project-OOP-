#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include "clsMenu.h"
#include "clsBankUser.h"
#include <iomanip>
class clsUserListScreen : protected clsMenu
{
private:
	static void _PrintUserRecordLine(clsBankUser user)
	{
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << user.Username;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << user.FirstName;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << user.LastName;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << user.Email;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << user.Phone;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << to_string(user.Permissions);
		cout << endl;
	}
public:
	static void ShowUserListScreen()
	{
		vector<clsBankUser> vUsers = clsBankUser::GetUsersList();
		string subTitle = "Users (" + to_string(vUsers.size()) + ") User/s";

		_ShowMenuHeader("USERS LIST SCREEN", subTitle);

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "USERNAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "FIRST NAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "LAST NAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "EMAIL";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "PHONE";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << "PERMISSIONS";
		cout << endl;
		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;

		if (vUsers.size() == 0)
		{
			cout << clsUtil::RED << string(20, ' ') << "THERE IS NO USERS TO SHOW THERE DATA." << endl;
		}
		else
		{
			for (short i = 0; i < vUsers.size(); i++)
			{
				_PrintUserRecordLine(vUsers.at(i));
			}
		}

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
	}
};

