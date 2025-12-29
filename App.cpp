#define NOMINMAX // to disable windows.h min/max macros
#include <iostream>
#include <iomanip>
#include "clsMainMenu.h"

using namespace std;

//void UpdateClient()
//{
//	cout << "Enter Account Number : ";
//	string AccNumber = clsInputValidation::ReadString();
//
//	while (!clsBankClient::IsExistClient(AccNumber))// validating client existence
//	{
//		cout << "Client not found, Enter Account Number: ";
//		AccNumber = clsInputValidation::ReadString();
//	}
//
//	clsBankClient client = clsBankClient::FindClient(AccNumber);
//	client.print();
//	cout << endl;
//	cout << "\nUpdate client " << endl;
//	cout << "----------------------------" << endl;
//	ReadClient(client);
//
//	clsBankClient::enSaveResults save;
//
//	save = client.Save();
//
//	switch (save)
//	{
//	case clsBankClient::enSaveResults::svFailedEmptyobject:
//		cout << "Update Failed Because the empty object." << endl;
//		break;
//	case clsBankClient::enSaveResults::svSucced:
//		cout << "Client Updated successfully" << endl;
//		break;
//	}
//
//}
//


void ShowTotalBalances()
{
	vector<clsBankClient> vClients = clsBankClient::GetClientsList();
	float Balance = clsBankClient::GetTotalBalance(vClients);

	cout << "\t\t\t\t\t Clients (" << vClients.size() << ") Client/s" << endl;
	cout << clsUtil::YELLOW << 
		"----------------------------------------------------------------------------" 
		<< clsUtil::RESET << endl;

	cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << "ACCOUNT NUMBER";
	cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << "CLIENT NAME";
	cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << "BALANCE";
	cout << endl;
	cout << clsUtil::YELLOW << 
		"----------------------------------------------------------------------------" << endl;
	if (vClients.size() == 0)
	{
		cout << clsUtil::RED << "THERE IS NO CLIENTS TO SHOW THERE BALANCE." << clsUtil:: RESET << endl;
	}
	else
	{
		for (short i = 0; i < vClients.size(); i++)
		{
			cout << clsUtil::RED << "| " << clsUtil::RESET << setw(25) << left << vClients.at(i).AccountNumber();
			cout << clsUtil::RED << "| " << clsUtil::RESET << setw(20) << left << vClients.at(i).FullName();
			cout << clsUtil::RED << "| " << clsUtil::RESET << setw(12) << left << to_string(vClients.at(i).Balance);
			cout << endl;
		}
	}
	cout << clsUtil::YELLOW << "----------------------------------------------------------------------------"<< endl;

	cout << clsUtil::RED << "TOTAL BALANCE : " << clsUtil::RESET << Balance << endl;
	cout << clsUtil::RED << "IN WORDS      : " << clsUtil::RESET << clsUtil::NumberToText((int)Balance) << endl;

	cout << clsUtil::YELLOW <<
		"----------------------------------------------------------------------------"
		<< clsUtil::RESET << endl;
	
	
}

int main()
{
	clsMainMenu::ShowMainMenu();
	
	return 0;
}