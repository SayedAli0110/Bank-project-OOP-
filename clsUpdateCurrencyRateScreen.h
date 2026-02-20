#pragma once
#include <iostream>
#include <vector>

#include "clsMenu.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"
#include "clsUtil.h"

using namespace std;

class clsUpdateCurrencyRateScreen : private clsMenu
{
public:
	static void ShowUpdateCurrencyRateScreen()
	{
		system("cls");
		_ShowMenuHeader("Update Currency Rate Screen");

		cout << "Enter Currency Code : ";
		string CurrencyCode = clsInputValidation::ReadString();

		clsCurrency Currency = clsCurrency::GetCurrencyByCode(CurrencyCode);

		while (Currency.IsEmpty())
		{
			cout << clsUtil::RED << "Currency with this code is not exist,please enter a valid one :" << clsUtil::RESET;
			CurrencyCode = clsInputValidation::ReadString();
			Currency = clsCurrency::GetCurrencyByCode(CurrencyCode);
		}

		cout << "\n";
		Currency.Print();

		cout << "Are you sure you want to update the rate for this currency ? (Y/N) : ";
		char answer;
		cin >> answer;

		while (tolower(answer) != 'y' && tolower(answer) != 'n')
		{
			cout << clsUtil::RED << "Invalid input, please enter Y for yes or N for no : " << clsUtil::RESET;
			cin >> answer;
		}

		if (tolower(answer) == 'y')
		{
			cout << "Enter new rate : ";
			float newRate = clsInputValidation::ReadFloatNumber();
			Currency.Rate = newRate;
			Currency.Update();
			cout << clsUtil::GREEN << "\nCurrency rate updated successfully." << clsUtil::RESET << endl;
		}
	}
};

