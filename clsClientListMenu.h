#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include "clsMenu.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientListMenu : protected clsMenu
{
private:
	static void _PrintClientRecordLine(clsBankClient client)
	{
		string encPin = client.PinCode;
		clsUtil::decrypt(encPin, 5);
		client.PinCode = encPin;

		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << client.AccountNumber();
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << client.FullName();
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << client.Phone;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << client.Email;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(10) << left << client.PinCode;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << to_string(client.Balance);
		cout << endl;
	}
public:
	static void ShowClientListMenu()
	{

		if (!CheckAccessRights(clsBankUser::enPermissions::eShowClenttsList))
		{
			return;
		}

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		string subTitle = "Clients (" + to_string(vClients.size()) + ") Client/s";
		_ShowMenuHeader("CLIENTS LIST SCREEN", subTitle);
		cout << clsUtil::YELLOW <<
			"---------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "ACCOUNT NUMBER";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "CLIENT NAME";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << "PHONE";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "EMAIL";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(10) << left << "PIN CODE";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << "BALANCE";
		cout << endl;
		cout << clsUtil::YELLOW <<
			"---------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
		if (vClients.size() == 0)
		{
			cout << clsUtil::RED <<string(20,' ') << "THERE IS NO CLIENTS TO SHOW THERE DATA." << endl;
		}
		else
		{
			for (short i = 0; i < vClients.size(); i++)
			{
				_PrintClientRecordLine(vClients.at(i));
			}
		}
		cout << clsUtil::YELLOW <<
			"---------------------------------------------------------------------------------------------------------------------"
			<< clsUtil::RESET << endl;
	}
};

