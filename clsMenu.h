#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include "clsUtil.h"
#include <conio.h>
#include <iomanip>
#include "clsBankUser.h"
#include "Global.h"

using namespace std;

class clsMenu
{
private:
	static void _PrintCurrentUser()
	{
		cout << setw(36) << "" << clsUtil::YELLOW << "User : " << clsUtil::RESET << CurrentUser.Username << endl;
	}
	static void _PrintLoginDate()
	{
		cout << setw(36) << "" << clsUtil::YELLOW << "Date : " << clsUtil::RESET;
		LoginDate.Print();
	}

public:
	static void _ShowMenuHeader(string Title, string subTitle = "")
	{
		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=') << clsUtil::RESET << endl;
		cout << setw(46) << "" << Title << endl;

		if (subTitle != "")
		{
			cout << setw(40)<< "" << clsUtil::YELLOW << subTitle << clsUtil::RESET << endl;
		}

		cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=') << clsUtil::RESET << endl;

		_PrintCurrentUser();
		_PrintLoginDate();
	}

	static bool CheckAccessRights(clsBankUser::enPermissions Permission)
	{
		if (CurrentUser.CheckUserPermission(Permission))
		{
			return true;
		}
		else
		{
			cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=') << endl;
			cout << setw(40) << "" << clsUtil::RED << "Access denied, contact your manager" << endl;
			cout << setw(35) << "" << clsUtil::YELLOW << string(40, '=')  << clsUtil::RESET << endl;

			return false;
		}

	}

	static short _PerformMenuOptions(vector<string> options, short StartLine = 0)
	{
	
		short selected = 0;
		short pos = StartLine;
		while (true)
		{
			// ensure any pending output is written before moving the cursor
			cout.flush();

			// position cursor to start (column 40, row 0) then redraw options
			clsUtil::MoveCursorTo(40, 1);
			pos = StartLine;

			// highlight selected option
			for (int i = 0; i < (int)options.size(); i++)
			{
				clsUtil::MoveCursorTo(40, pos);
				if (i == selected)
				{
					cout << clsUtil::RED;
					cout << options[i] << "\n";
				}
				else
				{
					cout << clsUtil::RESET;
					cout << options[i] << "\n";
				}
				pos++;
			}

			cout << setw(35) << "" << clsUtil::YELLOW << string(40, '-') << clsUtil::RESET << endl;

			// handle input
			char ch = _getch();

			if (ch == 0 || ch == -32) // arrow keys
			{
				switch (ch = _getch())
				{
				case 72: // up arrow
					if (selected == 0) selected = (short)(options.size() - 1);
					else selected--;
					break;
				case 80: // down arrow
					if (selected == (short)options.size() - 1) selected = 0;
					else selected++;
					break;
				}
			}
			else if (ch == 13) // enter key 
			{
				cout << clsUtil::RESET;
				return selected;
			}
		}
	}
};

