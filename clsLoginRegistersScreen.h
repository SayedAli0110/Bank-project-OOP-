#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsUtil.h"
#include "clsBankUser.h"
#include "clsMenu.h"

using namespace std;

class clsLoginRegistersScreen : clsMenu
{
private:

	static void _PrintRegisterRecord(vector<string> R)
	{
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << R.at(0);
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.at(1);
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << R.at(2);
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.at(3);
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.at(4);
		cout << endl;
	}
public:
	static void ShowLoginRegistersList()
	{
		vector<vector<string>> Registers = clsBankUser::LoadRegistersFromFile();
		system("cls");
		_ShowMenuHeader("LOGIN REGISTERS SCREEN");

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "DATE";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "TIME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "USER NAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "PASSWORD";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "PERMISSIONS";
		cout << endl;
		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;

		if (Registers.size() == 0)
		{
			cout << clsUtil::RED << string(20, ' ') << "THERE IS NO USERS TO SHOW THERE DATA." << endl;
		}
		else
		{
			for (short i = 0; i < Registers.size(); i++)
			{
				_PrintRegisterRecord(Registers.at(i));
			}
		}

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
	}
};

