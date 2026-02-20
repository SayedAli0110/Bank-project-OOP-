#pragma once

#include <iostream>
#include <vector>

#include "clsMenu.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"
#include "clsUtil.h"

using namespace std;

class clsCurrencyCalculator : private clsMenu
{
private:
	static clsCurrency _ReadCurrency(string msg)
	{
		cout << msg;
		string CurrencyCode = clsInputValidation::ReadString();
		clsCurrency Currency = clsCurrency::GetCurrencyByCode(CurrencyCode);

		while (Currency.IsEmpty())
		{
			cout << clsUtil::RED << "Currency with this code is not exist,please enter a valid one :" << clsUtil::RESET;
			CurrencyCode = clsInputValidation::ReadString();
			Currency = clsCurrency::GetCurrencyByCode(CurrencyCode);
		}

		return Currency;
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		system("cls");
		_ShowMenuHeader("Currency Calculator Screen");

		clsCurrency FromCurrency = _ReadCurrency("Enter the code of the currency you want to convert from : ");
		clsCurrency ToCurrency = _ReadCurrency("Enter the code of the currency you want to convert to : ");
		cout << "Enter the amount you want to convert : ";

		float Amount = clsInputValidation::ReadFloatNumber();

		float ConvertedAmount = (Amount / stof(FromCurrency.Rate)) * stof(ToCurrency.Rate);
		cout << clsUtil::GREEN << "\n" << Amount << " " << FromCurrency.Code << " is equal to " << ConvertedAmount << " " << ToCurrency.Code << "." << clsUtil::RESET << endl;
	}
};

