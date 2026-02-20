#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "clsUtil.h"
#include "clsMenu.h"
#include "clsCurrency.h"
#include "clsListCurrenciesMenu.h"
#include "clsFindCurrencyMenu.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculator.h"

using namespace std;
class clsCurrencyExchangeMainMenu : private clsMenu
{
private:
	enum enCurrencyExchangeMainMenuOptions
	{
		eShowCurrencyList = 0,
		eFindCurrency,
		eUpdateCurrencyRate,
		eCurrencyCalculator,
	};
	// menu option functions 
	static void _ShowCurrencyListScreen()
	{
		clsListCurrenciesMenu::ShowListCurrencisMenu();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyMenu::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculator::ShowCurrencyCalculatorScreen();
	}

	static void _GoBackToCurrencyExchangeMainMenu()
	{
		cout << "\nPress any key to go back to Currency Exchange Main Menu...";
		_getch();
	}

	static void _PerformCurrencyExchangeMainMenuOptions()
	{
		vector<string> options = { "Show Currency List", "Find Currency", "Update Currency Rate", "Currency Calculator"};

		short selectedOption = _PerformMenuOptions(options, 9);

		switch (selectedOption)
		{
		case enCurrencyExchangeMainMenuOptions::eShowCurrencyList:
			_ShowCurrencyListScreen();
			_GoBackToCurrencyExchangeMainMenu();
			break;
		case enCurrencyExchangeMainMenuOptions::eFindCurrency:
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMainMenu();
			break;
		case enCurrencyExchangeMainMenuOptions::eUpdateCurrencyRate:
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrencyExchangeMainMenu();
			break;
		case enCurrencyExchangeMainMenuOptions::eCurrencyCalculator:
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMainMenu();
			break;
		default:
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMainMenu()
	{
		system("cls");
		_ShowMenuHeader("\b\b\bCurrency Exchange Main Menu");

		cout << setw(35) << "" << string(40,'-') << endl;
		cout << setw(40) << "" << "Currency Main Menu" << endl;
		cout << setw(35) << "" << string(40, '-') << endl;

		_PerformCurrencyExchangeMainMenuOptions();

	}

};

