#define NOMINMAX // to disable windows.h min/max macros
#include <iostream>
#include <iomanip>
#include "clsLoginScreen.h"
#include "clsUtil.h"

using namespace std;

int main()
{
	while (true)
	{
		clsUtil::ShowCursor;
		clsLoginScreen::ShowLoginScreen();
	}
	return 0;
}