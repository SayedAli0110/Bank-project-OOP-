#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"

using namespace std;

// this is how data will be stored in the file 
// country, code , name, Rate

class clsCurrency
{
private:
	enum enMode { eEmpty = 0, eUpdate = 1 };
	enMode _Mode;
	string _Country;
	string _Name;
	string _Code;
	float _Rate;

	static string _TurnCurrencyDataIntoLine(clsCurrency Currency, string delim = "#//#")
	{
		string Line = "";
		Line += Currency._Country + delim;
		Line += Currency._Code + delim;
		Line += Currency._Name + delim;
		Line += to_string(Currency._Rate);

		return Line;
	}
	static clsCurrency _TurnLineIntoCurrencyData(string Line, string delim = "#//#")
	{
		clsCurrency Currency(enMode::eUpdate, "", "", "", 0);

		vector<string> vCurrencyData = clsString::Split(Line, delim);
		if (vCurrencyData.size() == 4)
		{
			Currency._Country = vCurrencyData[0];
			Currency._Code = vCurrencyData[1];
			Currency._Name = vCurrencyData[2];
			Currency._Rate = stof(vCurrencyData[3]);
			Currency._Mode = enMode::eUpdate;
		}

		return Currency;
	}

	static vector <clsCurrency> _LoadCurrenciesFromFile(string FileName)
	{
		vector<clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open(FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				vCurrencies.push_back(_TurnLineIntoCurrencyData(Line));
			}

			MyFile.close();
		}
		return vCurrencies;
	}

	bool _IsEmpty()
	{
		return _Mode == enMode::eEmpty;
	}

public:

	// constructors

	clsCurrency(enMode Mode, string Country, string Name, string Code, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_Name = Name;
		_Code = Code;
		_Rate = Rate;
	}

	// Read only properties
	string GetCountry() { return _Country; }
	string GetName() { return _Name; }
	string GetCode() { return _Code; }

	// Read and Write property
	string GetRate() { return to_string(_Rate); }
	void SetRate(float Rate) { _Rate = Rate; }

	__declspec(property(get = GetCountry)) string Country;
	__declspec(property(get = GetName)) string Name;
	__declspec(property(get = GetCode)) string Code;
	__declspec(property(get = GetRate, put = SetRate)) string Rate;

	// functions
	bool IsEmpty() 
	{ 
		return _IsEmpty(); 
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesFromFile("Currencies.txt");
	}

	static clsCurrency GetCurrencyByCode(string Code)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile("Currencies.txt");

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency._Code == clsString::UpperAllString(Code))
			{
				return Currency;
			}
		}
		return clsCurrency(enMode::eEmpty, "", "", "", 0);
	}

	static clsCurrency GetCurrencyByCountry(string Country)
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile("Currencies.txt");

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency._Country == clsString::UpperAllString(Country))
			{
				return Currency;
			}
		}
		return clsCurrency(enMode::eEmpty, "", "", "", 0);
	}

	static void printCurrency(clsCurrency Currency)
	{
		cout << "Currency Details: " << endl;
		cout << "======================================" << endl;
		cout << "Country : " << Currency._Country << endl;
		cout << "Name : " << Currency._Name << endl;
		cout << "Code : " << Currency._Code << endl;
		cout << "Rate : " << Currency.Rate << endl;
		cout << "======================================" << endl;
	}

	void Print()
	{
		printCurrency(*this);
	}

	void Update()
	{
		vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile("Currencies.txt");
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				if (Currency._Code == _Code)
				{
					Currency = *this;
				}

				MyFile << _TurnCurrencyDataIntoLine(Currency) << endl;
			}


			MyFile.close();
		}
	}
};

