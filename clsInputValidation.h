#pragma once
#pragma warning(disable : 4996)
#pragma warning (disable : 4267)

#include <iostream>
#include <ctime>
#include <limits>
#include "clsDate.h"


using namespace std;

class clsInputValidation
{
public:
	static bool IsNumberBetween(int number, int from, int to)
	{
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(float number, float from, float to)
	{
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(double number, double from, double to)
	{
		return (number >= from && number <= to);
	}

	static bool IsDateBetween(clsDate date, clsDate from, clsDate to)
	{
		if (from.CompareDates(to) == clsDate::enDateCompare::After)
		{
			clsDate temp = from;
			from = to;
			to = temp;
		}

		return (date.CompareDates(from) == clsDate::enDateCompare::After &&
			date.CompareDates(to) == clsDate::enDateCompare::Before);
	}

	static int ReadIntNumber(string message = "\nInvalid input, Enter a valid one: ")
	{
		int num;
		cin >> num;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message;
			cin >> num;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}

		return num;
	}

	static float ReadFloatNumber(string message = "\nInvalid input, Enter a valid one: ")
	{
		float num;
		cin >> num;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message;
			cin >> num;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		return num;
	}

	static double ReadDoubleNumber(string message = "\nInvalid input, Enter a valid one: ")
	{
		double num;
		cin >> num;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << message;
			cin >> num;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		return num;
	}

	static string ReadString()
	{
		string value;
		getline(cin >> ws, value);
		return value;
	}

	static int ReadIntNumberBetween(int x, int y)
	{
		int num = ReadIntNumber("\nInvalid Input Please Enter a Valid One : ");

		while (num < x || num > y)
		{
			cout << "\nThe number is not within the range" << endl;
			num = ReadIntNumber("\nInvalid Input Please Enter a Valid One : ");
		}

		return num;
	}

	static float ReadFloatNumberBetween(int x, int y)
	{
		float num = ReadFloatNumber("\nInvalid Input Please Enter a Valid One : ");

		while (num < x || num > y)
		{
			cout << "\nThe number is not within the range" << endl;
			num = ReadFloatNumber("\nInvalid Input Please Enter a Valid One : ");
		}

		return num;
	}

	static double ReadDoubleNumberBetween(int x, int y)
	{
		double num = ReadDoubleNumber("\nInvalid Input Please Enter a Valid One : ");

		while (num < x || num > y)
		{
			cout << "\nThe number is not within the range" << endl;
			num = ReadDoubleNumber("\nInvalid Input Please Enter a Valid One : ");
		}

		return num;
	}

	static bool ValidateDate(clsDate date)
	{
		if (date.Day < 1 || date.Day>31)
			return false;

		if (date.Month < 1 || date.Month>12)
			return false;

		if (date.Month == 2)
		{
			if (clsDate::isLeapYear(date.Year))
			{
				if (date.Day > 29)
					return false;
			}
			else
			{
				if (date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = clsDate::NumberOfDaysInAMonth(date.Month, date.Year);

		if (date.Day > DaysInMonth)
			return false;

		return true;

	}

};