#pragma once
#include <iostream>
#include "clsUtil.h"
#include "clsBankUser.h"
#include "clsMenu.h"
#include "Global.h"

using namespace std;

class clsTransferRegisterScreen : protected clsMenu
{
private:

	static void _PrintRegisterRecord(clsBankUser::TransferInfo R)
	{
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << R.Date;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.Time;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << R.FromUsername;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.ToUsername;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << to_string(R.Amount);
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << R.Username;
		cout << endl;
	}
public:
	static void ShowTransferRegistersList()
	{
		system("cls");

		if (!CheckAccessRights(clsBankUser::enPermissions::eShowTransferRegisters))
		{
			return;
		}

		vector<clsBankUser::TransferInfo> Transfers = clsBankUser::LoadTransferFromFile();
		_ShowMenuHeader("TRANSFER REGISTERS SCREEN");

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "DATE";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "TIME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "SENDER";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "RECIVER";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "AMOUNT";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "EMPLOYEE";
		cout << endl;
		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;

		if (Transfers.size() == 0)
		{
			cout << clsUtil::RED << string(20, ' ') << "THERE IS NO USERS TO SHOW THERE DATA." << endl;
		}
		else
		{
			for (short i = 0; i < Transfers.size(); i++)
			{
				_PrintRegisterRecord(Transfers.at(i));
			}
		}

		cout << clsUtil::YELLOW <<
			"------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
	}
};

