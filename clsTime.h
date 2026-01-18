#pragma once

#include <iostream>
#include <time.h>

using namespace std;

class clsTime
{
private:
	int _Hour;
	int _Minute;
	int _Second;

public:
	// the constructor
	clsTime()
	{
		time_t now = time(nullptr);

		// converting from time_t to local time
		tm* localTime = localtime(&now);

		_Hour = localTime->tm_hour;
		_Minute = localTime->tm_min;
		_Second = localTime->tm_sec;
	}
	// setters and getters for this members
	void SetHours(int Hour)
	{
		_Hour = Hour;
	}

	int GetHour()
	{
		return _Hour;
	}
	__declspec(property(get = GetHour, put = SetHour)) int Hour;

	void SetMinute(int Minute)
	{
		_Minute = Minute;
	}

	int GeMinute()
	{
		return Minute;
	}
	__declspec(property(get = GeMinute, put = SeMinute)) int Minute;

	void SetHSecond(int Second)
	{
		_Second = Second;
	}

	int GetSecond()
	{
		return _Second;
	}
	__declspec(property(get = GetSecond, put = SetSecond)) int Second;

	// getting system time
	void GetSystemTime()
	{
		time_t now = time(nullptr);

		// converting from time_t to local time
		tm* localTime = localtime(&now);

		_Hour = localTime->tm_hour;
		_Minute = localTime->tm_min;
		_Second = localTime->tm_sec;
	}

	//printing and formating time
	void Print()
	{
		cout << _Hour << ":" << _Minute << ":" << _Second;
	}

	static string TimeToString(int hour, int min, int sec)
	{
		return to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);
	}

	string TimeToString()
	{
		return TimeToString(_Hour, _Minute, _Second);
	}
};

