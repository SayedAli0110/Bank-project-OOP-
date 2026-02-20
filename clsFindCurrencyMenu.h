#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>

#include "clsUtil.h"
#include "clsMenu.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"

class clsFindCurrencyMenu : private clsMenu
{
private:
	static short _ShowHorizentalChoices()
	{
		vector<string> options = { "Name", "Code" };

		short selectedOption = 0;
		while (true)
		{

			// printing the menu 
			clsUtil::MoveCursorTo(0, 4);
			cout << "Search By: ";

			for (short i = 0; i < options.size(); i++)
			{
				if (i == selectedOption)
				{
					cout << clsUtil::RED;
				}
				cout << options.at(i) << " " << clsUtil::RESET;
			}

			//getting a seletcted option

			short choice = _getch();
			
			if (choice == 0 || choice == 224)
			{
				choice = _getch();

				switch (choice)
				{
				case 75: // left arrow
	
					(selectedOption == 0) ? selectedOption = 1 : selectedOption--;

					break;
				case 77: //right arrow 
					(selectedOption == 1) ? selectedOption = 0 : selectedOption++;
					break;
				}
			}
			else if (choice == 13) // enter key
			{
				break;
			}
		}
		return selectedOption;

	}

public:
	static void ShowFindCurrencyScreen()
	{
		system("cls");
		_ShowMenuHeader("Find Currency Screen");

		short choice = _ShowHorizentalChoices();

		if (choice == 0)
		{
			cout << "\n" << "Enter Country Name: ";
			string Country = clsInputValidation::ReadString();
			clsCurrency Currency = clsCurrency::GetCurrencyByCountry(Country);
			
			while (Currency.IsEmpty()) // validatin if the country is exist
			{
				cout << clsUtil::RED << "Cannot find a country with this name\n";
				cout << clsUtil::RESET << "Enter a Country name: ";
				string Country = clsInputValidation::ReadString();
				clsCurrency Currency = clsCurrency::GetCurrencyByCountry(Country);
			}

			cout << endl << clsUtil::GREEN << "Currency is found successfuly " << clsUtil::RESET << endl;
			Currency.Print();
		}
		else if (choice == 1)
		{
			cout << "\n" << "Enter Country Code: ";
			string Code = clsInputValidation::ReadString();
			clsCurrency Currency = clsCurrency::GetCurrencyByCode(Code);

			while (Currency.IsEmpty()) // validatin if the country is exist
			{
				cout << clsUtil::RED << "Cannot find a country with this code\n";
				cout << clsUtil::RESET << "Enter a Country code: ";
				string Code = clsInputValidation::ReadString();
				clsCurrency Currency = clsCurrency::GetCurrencyByCode(Code);
			}

			cout << endl << clsUtil::GREEN << "Currency is found successfuly " << clsUtil::RESET << endl;
			Currency.Print();
		}

		
	}
};

