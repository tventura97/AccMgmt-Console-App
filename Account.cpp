//#include "stdafx.h"
#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(double A)
{
    cashBalance = A;
}

Account::~Account()
{
    cout << "ated" << endl;
}
