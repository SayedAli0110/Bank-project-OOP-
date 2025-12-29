#pragma once
#pragma warning (disable : 4267)

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "clsUtil.h"
#include <conio.h>
#include <iomanip>

using namespace std;

class clsMenu
{
public:
	static void _ShowMenuHeader(string Title, string subTitle = "")
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD defaultAttrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		cout << endl;
		// yellow-ish separator
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << setw(35) << "" << string(40, '-') << endl;

		// title in default color (or change attributes if you prefer)
		SetConsoleTextAttribute(hConsole, defaultAttrs);
		cout << setw(37) << "\t" << Title << endl;

		if (subTitle != "")
		{
			// subtitle in yellow-ish
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << setw(37)<< "\t" << subTitle << endl;
		}

		// closing separator
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << setw(35) << "" << string(40, '-') << endl;
		SetConsoleTextAttribute(hConsole, defaultAttrs);
		cout << "\n";
	}
	static short _PerformMenuOptions(vector<string> options, short StartLine = 0)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		WORD defaultAttrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		if (GetConsoleScreenBufferInfo(hConsole, &csbi))
			defaultAttrs = csbi.wAttributes;

		short selected = 0;
		short pos = StartLine;
		COORD coord = { 40 , pos };
		while (true)
		{
			// ensure any pending output is written before moving the cursor
			cout.flush();

			// position cursor to start (column 40, row 0) then redraw options
			SetConsoleCursorPosition(hConsole, { 40,0 });
			pos = StartLine;

			// highlight selected option
			for (int i = 0; i < (int)options.size(); i++)
			{
				coord = { 44, pos };
				SetConsoleCursorPosition(hConsole, coord);
				if (i == selected)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << options[i] << "\n";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, defaultAttrs);
					cout << options[i] << "\n";
				}
				pos++;
			}

			// print separator using Win32 attributes (avoid ANSI here)
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << setw(35) << "" << string(40, '-') << endl;
			SetConsoleTextAttribute(hConsole, defaultAttrs);

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
				// restore default attribute before returning
				SetConsoleTextAttribute(hConsole, defaultAttrs);
				return selected;
			}
		}
	}
};

