#pragma once

#include <iostream>
#include "clsBankUser.h"
#include "clsDate.h"

using namespace std;

clsBankUser CurrentUser = clsBankUser::GetEmptyUser();

clsDate LoginDate = clsDate::GetSystemDate();