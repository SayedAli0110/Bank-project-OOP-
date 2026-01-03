#pragma once
#pragma warning(disable : 4996)
#pragma warning (disable : 4267)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsDate.h"
#include "clsPeriod.h"

using namespace std;

class clsUtil {
public:
	enum EnRandomCharacterOptions {
		LowerCase = 1,
		UpperCase = 2,
		Digits = 3,
		mixed = 4
	};

	static void Pause()
	{
		cout << "Press Enter to continue...";
		cin.ignore();
	}

	static void ClearScreen()
	{
		system("cls");
	}

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		return (rand() % (To - From + 1)) + From;
	}

	static char RandomCharacter(EnRandomCharacterOptions CharCase)
	{
		switch (CharCase)
		{
		case EnRandomCharacterOptions::LowerCase:
			return char(RandomNumber(97, 122)); // a-z
			break;
		case EnRandomCharacterOptions::UpperCase:
			return char(RandomNumber(65, 90)); // A-Z
			break;
		case EnRandomCharacterOptions::Digits:
			return char(RandomNumber(48, 57)); // 0-9
			break;
		case EnRandomCharacterOptions::mixed:
			return RandomCharacter((EnRandomCharacterOptions)RandomNumber(1, 3));
			break;
		default:
			return ' ';
			break;
		}
	}

	static string RandomWord(short Length, EnRandomCharacterOptions WordCase)
	{
		string result = "";
		for (short i = 0; i < Length; i++)
		{
			result += RandomCharacter(WordCase);
		}
		return result;
	}

	static string RandomKey(short Length, EnRandomCharacterOptions KeyCase)
	{
		string Key = "";
		for (short i = 0; i < 3; i++)
		{
			Key += RandomWord(Length, KeyCase);
			Key += "-";
		}
		Key += RandomWord(Length, KeyCase);

		return Key;
	}

	static void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	static void Swap(string& a, string& b)
	{
		string temp = a;
		a = b;
		b = temp;
	}

	static void Swap(float& a, float& b)
	{
		float temp = a;
		a = b;
		b = temp;
	}

	static void Swap(double& a, double& b)
	{
		double temp = a;
		a = b;
		b = temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	static void Swap(clsPeriod& Period1, clsPeriod& Period2)
	{
		clsPeriod TempPeriod = Period1;
		Period1 = Period2;
		Period2 = TempPeriod;
	}

	static void shuffle(vector<int>& arr)
	{
		for (size_t i = 0; i < arr.size(); i++)
		{
			Swap(arr.at(i), arr.at(RandomNumber(0, arr.size() - 1)));
		}
	}

	static void shuffle(vector<float>& arr)
	{
		for (size_t i = 0; i < arr.size(); i++)
		{
			Swap(arr.at(i), arr.at(RandomNumber(0, arr.size() - 1)));
		}
	}

	static void shuffle(vector<double>& arr)
	{
		for (size_t i = 0; i < arr.size(); i++)
		{
			Swap(arr.at(i), arr.at(RandomNumber(0, arr.size() - 1)));
		}
	}

	static void shuffle(vector<string>& arr)
	{
		for (size_t i = 0; i < arr.size(); i++)
		{
			Swap(arr.at(i), arr.at(RandomNumber(0, arr.size() - 1)));
		}
	}

	static vector<int> FillArrayWithRandomNumbers(short ArrLength, int From, int To)
	{
		vector<int> arr;
		for (short i = 0; i < ArrLength; i++)
		{
			arr.push_back(RandomNumber(From, To));
		}
		return arr;
	}

	static vector<string> FillArrayWithRandomWords(short ArrLength, short WrdLength, EnRandomCharacterOptions WordsCase)
	{
		vector<string> arr;
		for (int i = 0; i < ArrLength; i++)
		{
			arr.push_back(RandomWord(WrdLength, WordsCase));
		}

		return arr;
	}

	static vector<string> FillArrayWithRandomKeys(short ArrLength, short WrdLength, EnRandomCharacterOptions KeyCase)
	{
		vector<string> arr;
		for (int i = 0; i < ArrLength; i++)
		{
			arr.push_back(RandomKey(WrdLength, KeyCase));
		}
		return arr;
	}

	static void encrypt(string& word, int EnKey)
	{
		for (short i = 0; i < word.length(); i++)
		{
			word[i] = char(int(word[i]) + EnKey);
		}
	}

	static void decrypt(string& word, int DeKey)
	{
		for (short i = 0; i < word.length(); i++)
		{
			word[i] = char(int(word[i]) - DeKey);
		}
	}

	static const string RED;
	static const string GREEN;
	static const string YELLOW;
	static const string BLUE;
	static const string MAGENTA;
	static const string CYAN;
	static const string RESET;
	static const string RemoveCursor;
	static const string ShowCursor;

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}


};

const string clsUtil::RED = "\033[31m";
const string clsUtil::GREEN = "\033[32m";
const string clsUtil::YELLOW = "\033[33m";
const string clsUtil::BLUE = "\033[34m";
const string clsUtil::MAGENTA = "\033[35m";
const string clsUtil::CYAN = "\033[36m";
const string clsUtil::RESET = "\033[0m";
const string clsUtil::RemoveCursor = "\033[?25l";
const string clsUtil::ShowCursor = "\033[?25h";

