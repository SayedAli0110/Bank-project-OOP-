#pragma once
#pragma warning(disable : 4996)
#pragma warning (disable : 4267)

#include <iostream>

using namespace std;
class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _phone;

public:
	// constructor
	clsPerson(string FirstName, string LastName, string Email, string Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_phone = Phone;
	}
	// setters and getters
	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}
	string GetFirstName()
	{
		return _FirstName;
	}
	__declspec(property(get = GetFirstName, put = SetFirstName))string FirstName;

	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}
	string GetLastName()
	{
		return _LastName;
	}
	__declspec(property(get = GetLastName, put = SetLastName))string LastName;

	void SetEmail(string Email)
	{
		_Email = Email;
	}
	string GetEmail()
	{
		return _Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail))string Email;

	void SetPhone(string Phone)
	{
		_phone = Phone;
	}
	string GetPhone()
	{
		return _phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone))string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}
};