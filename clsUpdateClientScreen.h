#pragma once 
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMenu.h"
#include "clsUtil.h"

using namespace std;

class clsUpdateClientScreen : protected clsMenu
{
protected:
	static void _ReadClient(clsBankClient& client)
	{
		cout  << "FIRST NAME: ";
		client.FirstName = clsInputValidation::ReadString();
		cout  << "LAST NAME : ";
		client.LastName = clsInputValidation::ReadString();
		cout  << "EMAIL     : ";
		client.Email = clsInputValidation::ReadString();
		cout  << "PHONE     : ";
		client.Phone = clsInputValidation::ReadString();
		cout  << "PIN CODE  : ";
		client.PinCode = clsInputValidation::ReadString();
		cout  << "Balance   : ";
		client.Balance = clsInputValidation::ReadFloatNumber();
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

public:
	static void ShowUpdateClientScreen()
	{

		if (!CheckAccessRights(clsBankUser::enPermissions::eUpdateClient))
		{
			return;
		}

		_ShowMenuHeader("UPDATE CLIENT SCREEN");
		cout << "Enter Account Number : ";
		string AccNumber = clsInputValidation::ReadString();
		while (!clsBankClient::IsExistClient(AccNumber))// validating client existence
		{
			cout << clsUtil::RED << "Client not found." << clsUtil::RESET << endl;
			cout << "Enter Account Number: ";
			AccNumber = clsInputValidation::ReadString();
		}
		clsBankClient client = clsBankClient::FindClient(AccNumber);
		_PrintClient(client);
		cout << endl;
		cout << "Update client " << endl;
		cout << clsUtil::YELLOW << "----------------------------" << clsUtil::RESET<< endl;
		_ReadClient(client);

		switch (client.Save())
		{
		case clsBankClient::enSaveResults::svFailedEmptyobject:
			cout << clsUtil::RED << "Update Failed Because the empty object." << clsUtil::RESET << endl;
			break;
		case clsBankClient::enSaveResults::svSucced:
			cout << clsUtil::GREEN << "Client Updated successfully" << clsUtil::RESET << endl;
			break;
		}

	}

};

