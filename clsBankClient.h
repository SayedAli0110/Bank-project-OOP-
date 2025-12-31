#pragma once
#pragma warning(disable : 4996)
#pragma warning (disable : 4267)
#pragma warning (disable : 4715)

#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"
#include "clsUtil.h"
#include "clsPerson.h"
#include <fstream>

// this is how data will be saved in record
// FirstName, LastName, Email, phone, AccNumber , pinCode, balance

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1,
		ADDMode = 2
	};
	enMode _Mode;
	string _AccNumber;
	string _PinCode;
	float _Balance;
	bool _MarkToDlete = false;

	static clsBankClient _convertLineIntoClientObject(string DataLine, string seperator = "#//#")
	{
		clsString value(DataLine);

		vector<string> vstring = value.Split(seperator);

		return clsBankClient
		(vstring[0], vstring[1], vstring[2], vstring[3], vstring[4], vstring[5], stof(vstring[6]), enMode::UpdateMode);
	}

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient("", "", "", "", "" ,"", 0, enMode::EmptyMode);
	}

	static string _ConvertClientObjecIntoLine(clsBankClient Client, string seperator = "#//#")
	{
		string line = "";
		line += Client.FirstName + seperator;
		line += Client.LastName + seperator;
		line += Client.Email + seperator;
		line += Client.Phone + seperator;
		line += Client.AccountNumber() + seperator;
		line += Client.PinCode + seperator;
		line += to_string(Client.Balance);

		return line;
	}

	static vector<clsBankClient> _LoadClientsFromFile(string FileName = "Clients.txt")
	{
		vector<clsBankClient> output;
		string clientLine;

		fstream fclients;
		fclients.open(FileName, ios::in);

		if (fclients.is_open())
		{
			while (getline(fclients, clientLine))
			{
				output.push_back(_convertLineIntoClientObject(clientLine));
			}
			fclients.close();
		}

		return output;
	}

	static void _SaveClientsToFile(vector<clsBankClient> Clients)
	{
		fstream fClients;
		fClients.open("Clients.txt", ios::out); //overwrite mode

		if (fClients.is_open())
		{
			for (clsBankClient& c : Clients)
			{
				fClients << _ConvertClientObjecIntoLine(c) << endl;
				
			}
		}

		fClients.close();
	}

	static void _AddClientToFile(string ClientRecordLine)
	{

		fstream fClients;
		fClients.open("Clients.txt", ios::app | ios::out);
		
		if (fClients.is_open())
		{
			fClients << ClientRecordLine << endl;
		}
		fClients.close();
	}

	static void _SaveClientDataToFile(vector<clsBankClient> vClients, string FileName = "Clients.txt")
	{
		fstream fClients;
		fClients.open(FileName, ios::out);
		if(fClients.is_open())
		{
			for (clsBankClient& c : vClients)
			{
				if (!c.MarkToDelete)
				{
					fClients << _ConvertClientObjecIntoLine(c) << endl; 
				}
			}
		}
	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientsFromFile("Clients.txt");

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == AccountNumber())
			{
				c = *this;
			}
		}

		_SaveClientsToFile(vClients);
	}
	void _AddNew()
	{
		_AddClientToFile(_ConvertClientObjecIntoLine(*this));
	}

	static bool _IsEmpty(clsBankClient Client)
	{
		return (Client._Mode == enMode::EmptyMode);
	}

public:
	//constructor
	clsBankClient(string FirstName, string LastName, string Email,
		string phone, string AccNo, string PinCode, float Balance, enMode Mode) : clsPerson(FirstName, LastName, Email, phone)
	{
		_Mode = Mode;
		_AccNumber = AccNo;
		_PinCode = PinCode;
		_Balance = Balance;
	}
	
	// Read only property
	string AccountNumber()
	{
		return _AccNumber;
	}

	// setters and getters 
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetBalance(float Balance)
	{
		_Balance = Balance;
	}
	float GetBalance()
	{
		return _Balance;
	}
	__declspec(property(get = GetBalance, put = SetBalance)) float Balance;

	void SetMarktd(bool Mark)
	{
		_MarkToDlete = Mark;
	}
	bool GetMarktd()
	{
		return _MarkToDlete;
	}
	__declspec(property(get = GetMarktd, put = SetMarktd)) bool MarkToDelete;

	// class methods
	static clsBankClient FindClient(string AccNumber)
	{
		string line;
		fstream fClients;
		fClients.open("Clients.txt", ios::in);

		if (fClients.is_open())
		{
			while (getline(fClients, line))
			{
				clsBankClient client = _convertLineIntoClientObject(line);
				if (client.AccountNumber() == AccNumber)
				{
					fClients.close();
					return client;
				}
			}
			fClients.close();
		}
		return _GetEmptyClient();
	}

	static clsBankClient FindClient(string AccNumber, string Password)
	{
		string line;
		fstream fClients;
		fClients.open("Clients.txt", ios::in);

		if (fClients.is_open())
		{
			while (getline(fClients, line))
			{
				clsBankClient client = _convertLineIntoClientObject(line);
				if (client.AccountNumber() == AccNumber && client.PinCode == Password)
				{
					fClients.close();
					return client;
				}
			}
			fClients.close();
			return _GetEmptyClient();
		}
	}

	static bool IsExistClient(string AccNumber)
	{
		clsBankClient client = clsBankClient::FindClient(AccNumber);
		return (!_IsEmpty(client));
	}

	static clsBankClient GetAddNewClient(string AccountNumber)
	{
		return clsBankClient("", "", "", "", AccountNumber, "", 0, enMode::ADDMode);
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsFromFile();
	}

	static float GetTotalBalance(vector<clsBankClient> vClients)
	{
		float output = 0;
		for (clsBankClient& c : vClients)
		{
			output += c.Balance;
		}

		return output;
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadClientsFromFile("Clients.txt");

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == _AccNumber)
			{
				c.MarkToDelete = true;
			}
		}

		_SaveClientDataToFile(vClients);

		*this = _GetEmptyClient();
		
		return _IsEmpty(*this);
	}

	bool Deposit(float Amount)
	{
		
		if(Amount <= 0)
		{
			return false;
		}
		else
		{
			_Balance += Amount;
			Save();
		}
		return true;
	}

	bool Withdraw(float Amount)
	{
		if (Amount > _Balance || Amount <= 0)
		{
			return false;

		}
		else
		{
			_Balance -= Amount;
			Save();
		}
			return true;
	}

	enum enSaveResults
	{
		svFailedEmptyobject = 0,
		svFailedExistObject = 1,
		svSucced = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyobject;
			break;
		case enMode::UpdateMode:
			_Update();
			return svSucced;
			break;
		case enMode::ADDMode:
			if (IsExistClient(_AccNumber))
			{
				return enSaveResults::svFailedExistObject;
			}
			else
			{
				_AddNew();
				_Mode = UpdateMode;
				return svSucced;
			}
			break;
		}
	}
	
};

