#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "clsUtil.h"
#include "clsMenu.h"
#include "clsCurrency.h"

using namespace std;

class clsListCurrenciesMenu : private clsMenu
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(30) << left << Currency.Country;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(40) << left << Currency.Name;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << Currency.Code;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << Currency.Rate;
		cout << endl;
	}

	static void _PrintHeader()
	{
		cout << clsUtil::YELLOW << string(106, '-') << clsUtil::RESET << endl;
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(30) << left << "Country";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(40) << left << "Currency Name";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "Currency Code";
		cout << clsUtil::RED << "| " << clsUtil::RESET << setw(15) << left << "Currency Rate";
		cout << endl;
		cout << clsUtil::YELLOW << string(106, '-') << clsUtil::RESET << endl;
	}

public:
	static void ShowListCurrencisMenu()
	{
		system("cls");

		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string subtitle = "\b\b\b\b" + to_string(vCurrencies.size()) + " Currency(s) Available In The System";
		_ShowMenuHeader("List Currencies");

		_PrintHeader();
		
		if (vCurrencies.size() == 0)
		{
			cout << clsUtil::RED << "No Currencies Available In The System!" << clsUtil::RESET << endl;
		}
		else
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyRecordLine(Currency);
			}
		}
		
	}
};

