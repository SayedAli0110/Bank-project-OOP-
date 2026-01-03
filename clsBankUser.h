#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsInputValidation.h"

using namespace std;

string FileName = "Users.txt";

class clsBankUser : public clsPerson
{
private:
	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1,
		ADDMode = 2
	};
	enMode _Mode;
	string _Username;
	string _Password;
	int permissions;

	bool MarkToDelete = false;

	static clsBankUser _convertLineIntoUserObject(string DataLine, string seperator = "#//#")
	{
		clsString value(DataLine);

		vector<string> vstring = value.Split(seperator);

		return clsBankUser
		(enMode::UpdateMode ,vstring[0], vstring[1], vstring[2], vstring[3], vstring[4], vstring[5], stoi(vstring[6]));
	}


	static string _ConvertUserObjecIntoLine(clsBankUser User, string seperator = "#//#")
	{
		string line = "";
		line += User.FirstName + seperator;
		line += User.LastName + seperator;
		line += User.Email + seperator;
		line += User.Phone + seperator;
		line += User.Username + seperator;
		line += User.Password + seperator;
		line += to_string(User.Permissions);

		return line;
	}

	static vector<clsBankUser> _LoadUsersFromFile()
	{
		vector<clsBankUser> output;
		string UserLine;

		fstream fUsers;
		fUsers.open(FileName, ios::in);

		if (fUsers.is_open())
		{
			while (getline(fUsers, UserLine))
			{
				output.push_back(_convertLineIntoUserObject(UserLine));
			}
			fUsers.close();
		}

		return output;
	}

	static void _AddUserToFile(string UserRecordLine)
	{

		fstream fUsers;
		fUsers.open(FileName, ios::app | ios::out);

		if (fUsers.is_open())
		{
			fUsers << UserRecordLine << endl;
		}
		fUsers.close();
	}

	static void _SaveUsersDataToFile(vector<clsBankUser> vUsers)
	{
		fstream fUsers;
		fUsers.open(FileName, ios::out);
		if (fUsers.is_open())
		{
			for (clsBankUser& c : vUsers)
			{
				if (!c.MarkToDelete)
				{
					fUsers << _ConvertUserObjecIntoLine(c) << endl;
				}
			}
		}
		fUsers.close();
	}


	void _update()
	{
		vector<clsBankUser> vUsers = _LoadUsersFromFile();

		for (clsBankUser& c : vUsers)
		{
			if (c.Username == _Username)
			{
				c = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}

	void _Add()
	{
		_AddUserToFile(_ConvertUserObjecIntoLine(*this));
	}

public:

	// constructor
	clsBankUser(enMode mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = mode;
		_Username = Username;
		_Password = Password;
		permissions = Permissions;
	}

	// setters and getters
	void SetUsername(string Username)
	{
		_Username = Username;
	}
	string GetUsername()
	{
		return _Username;
	}
	__declspec(property(get = GetUsername, put = SetUsername))string Username;


	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;


	void SetPermissions(int Permissions)
	{
		permissions = Permissions;
	}
	int GetPermissions()
	{
		return permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions))int Permissions;

	// other class methods

	static clsBankUser FindUser(string Username)
	{
		vector<clsBankUser> vUsers = _LoadUsersFromFile();
		for (clsBankUser& user : vUsers)
		{
			if (user.Username == Username)
			{
				return user;
			}
		}

		return GetEmptyUser();
	}

	static clsBankUser FindUser(string Username, string Password)
	{
		vector <clsBankUser> vUsers = _LoadUsersFromFile();
		for (clsBankUser& user : vUsers)
		{
			if (user.Username == Username && user.Password == Password)
			{
				return user;
			}
		}

		return GetEmptyUser();
	}

	static clsBankUser GetAddNewUser(string Username)
	{
		return clsBankUser(enMode::ADDMode, "", "", "", "", Username, "", 0);
	}
	
	static clsBankUser GetEmptyUser()
	{
		return clsBankUser(enMode::EmptyMode,"", "", "", "", "", "", 0);
	}

	static bool IsExistUser(string Username)
	{
		clsBankUser user = clsBankUser::FindUser(Username);
		return (user._Mode != enMode::EmptyMode);
	}

	static vector<clsBankUser> GetUsersList()
	{
		return _LoadUsersFromFile();
	}

	bool Delete()
	{
		vector<clsBankUser> vUsers = _LoadUsersFromFile();

		for (clsBankUser& u : vUsers)
		{
			if (u.Username == _Username)
			{
				u.MarkToDelete = true;
				*this = GetEmptyUser();
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		return (_Mode == enMode::EmptyMode);
	}
	
	enum enSaveResults { svFaildEmptyObject = 0, svFaildUserExists = 1, svSucceedAddNewUser = 2, svSucceedUpdateUser = 3 };

	void Update()
	{
		_Mode = enMode::UpdateMode;
	}

	enSaveResults Save()
	{
		if (_Mode == enMode::EmptyMode)
		{
			return enSaveResults::svFaildEmptyObject;
		}
		if (_Mode == enMode::ADDMode)
		{
			if (IsExistUser(_Username))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_Add();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceedAddNewUser;
			}
		}
		if (_Mode == enMode::UpdateMode)
		{
			_update();
			return enSaveResults::svSucceedUpdateUser;
		}
	}


};

