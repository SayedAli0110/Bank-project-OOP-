#pragma once 
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"
#include <vector>
#include <string>

using namespace std;

class clsUpdateClientScreen : protected clsMenu
{
private:
	static void _ReadClient(clsBankClient& client)
	{
		cout  << "FIRST NAME : ";
		client.FirstName = clsInputValidation::ReadString();
		cout  << "LAST NAME  : ";
		client.LastName = clsInputValidation::ReadString();
		cout  << "EMAIL      : ";
		client.Email = clsInputValidation::ReadString();
		cout  << "PHONE      : ";
		client.Phone = clsInputValidation::ReadString();
		cout  << "PIN CODE   : ";
		client.PinCode = clsInputValidation::ReadString();

	}

	static void _PrintClient(clsBankClient client)
	{
		cout << "        CLIENT CARD" << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET << endl;
		cout << "FIRST NAME: " << client.FirstName << endl;
		cout << "LAST NAME : " << client.LastName << endl;
		cout << "FULL NAME : " << client.FullName() << endl;
		cout << "EMAIL     : " << client.Email << endl;
		cout << "PHONE     : " << client.Phone << endl;
		cout << "PIN CODE  : " << client.PinCode << endl;
		cout << "Balance   : " << client.Balance << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET;
	}

	static void _UpdateClientName(clsBankClient& client)
	{
		cout << "Enter New First Name: ";
		client.FirstName = clsInputValidation::ReadString();
		cout << "Enter New Last Name: ";
		client.LastName = clsInputValidation::ReadString();
	}

	static void _UpdateClientEmail(clsBankClient& client)
	{
		cout << "Enter New Email: ";
		client.Email = clsInputValidation::ReadString();
	}

	static void _UpdateClientPhone(clsBankClient& client)
	{
		cout << "Enter New Phone: ";
		client.Phone = clsInputValidation::ReadString();
	}

	static void _UpdateClientPinCode(clsBankClient& client)
	{
		cout << "Enter New Pin Code: ";
		client.PinCode = clsInputValidation::ReadString();
	}


public:
	static void ShowUpdateClientScreen()
	{

		if (!CheckAccessRights(clsBankUser::enPermissions::eUpdateClient))
		{
			return;
		}

		_ShowMenuHeader("UPDATE CLIENT SCREEN");

		short CurrentLine = 8;

		cout << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();

		while (!clsBankClient::IsExistClient(AccNumber))// validating client existence
		{
			system("cls");
			_ShowMenuHeader("UPDATE CLIENT SCREEN", "Client not found.");
			cout << "Enter Account Number: ";
			AccNumber = clsInputValidation::ReadString();
		}

		clsBankClient client = clsBankClient::FindClient(AccNumber);

		vector<string> vTargetUpdateItem =
		{
		  "1-Name",
		  "2-Email",
		  "3-Phone",
		  "4-Pin Code",
		  "5-All",
		  "6-Exit"
		};

		enum enUpdateMenuOptions
		{
			eUpdateName = 0,
			eUpdateEmail = 1,
			eUpdatePhone = 2,
			eUpdatePinCode = 3,
			eUpdateAll = 4,
			eExit = 5
		};

		clsUtil::MoveCursorTo(0, CurrentLine-2);
		cout << setw(35) << "" << endl;
		cout << setw(35) << "" << "Choose what do you want to update for this client?" << endl;
		CurrentLine++;
		short SelectedItem;

		SelectedItem = _PerformMenuOptions(vTargetUpdateItem, CurrentLine);
		switch (SelectedItem)
		{
		case enUpdateMenuOptions::eUpdateName:
			_UpdateClientName(client);
			break;
		case enUpdateMenuOptions::eUpdateEmail:
			_UpdateClientEmail(client);
			break;
		case enUpdateMenuOptions::eUpdatePhone:
			_UpdateClientPhone(client);
			break;
		case enUpdateMenuOptions::eUpdatePinCode:
			_UpdateClientPinCode(client);
			break;
		case enUpdateMenuOptions::eUpdateAll:
			_ReadClient(client);
			break;

		default:
			break;
		}

		switch (client.Save())
		{
		case clsBankClient::enSaveResults::svFailedEmptyobject:
			cout << setw(35) << "" << clsUtil::RED << "Update Failed Because the empty object." << clsUtil::RESET << endl;
			break;
		case clsBankClient::enSaveResults::svSucced:
			cout << setw(35) << "" << clsUtil::GREEN << "Client Updated successfully" << clsUtil::RESET << endl;
			break;
		}
		cout << setw(35) << "" << clsUtil::YELLOW << "----------------------------------------" << clsUtil::RESET << endl;

	}

};

