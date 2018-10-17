//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Account.h"
#include "stockAccount.h"
#include <string>
#include <cstdlib>
#include "time.h"
#include <stdio.h>
#include <codecvt>
#include <vector>
#include <locale>
#include <math.h>
#include <ctime>
#include "bankAccount.h"
#include <iomanip>
using namespace std;



bankAccount::bankAccount(double A) : stockAccount(A)
{

    ofstream myfile;
    string Line = "\nAction\t\tAmount\t\tCash Balance\t\tDate\t\tTime\n";
    myfile.open("BankTransactions.txt", ios_base::app);
    myfile << Line;
    myfile.close();


}

bankAccount::~bankAccount()
{
    cout << "Program ";
}


void bankAccount::deposit()
{   
    char LINE[256];
    double deposit;
    int flag = 0;
    cout << "Please enter amount for deposit: ";
    cin.getline(LINE, 256);
    deposit = stof(LINE);
    cout << deposit << endl;
    if (deposit < 0)
    {
        cout << "Invalid amount" << endl;
        flag = 1;
    }
    if (flag == 0)
    {
        cashBalance+=deposit;
        printf("\nDeposit $%.2f to account.\n", deposit);
        displayCurrentPortfolio();
        cout << endl;
        writebankTransaction("Deposit", deposit);
        flag = 0;
    }


}


void bankAccount::withdraw()
{
    char LINE[256];
    double withdrawl;
    int flag = 0;
    cout << "Please enter amount for withdrawl: ";
    cin.getline(LINE, 256);
    withdrawl = stof(LINE);
    cout << withdrawl << endl;
    if (withdrawl < 0)
    {
        cout << "Invalid amount" << endl;
        flag = 1;
    }
    if (withdrawl > cashBalance)
    {
        cout << "Insufficient funds" << endl;
        flag = 1;
    }
    if (flag == 0)
    {
        cashBalance-=withdrawl;
        printf("\nWithdraw $%.2f from account.\n", withdrawl);
        displayCurrentPortfolio();
        cout << endl;
        writebankTransaction("Withdrawl", withdrawl);
        flag = 0;
    }



}

void bankAccount::writebankTransaction(string action, double amount)
{


    ofstream myfile;
    string tab;
    if (action == "Withdrawl")
    {
        tab = "\t";

    }
    else if (action == "Deposit")
    {
        tab = "\t\t";
    }
    myfile.open("BankTransactions.txt", ios_base::app);
    string Line = action+tab;
    myfile << Line;
    myfile << fixed << setprecision(2) << amount;
    Line = "\t\t$";
    myfile << Line;
    myfile << cashBalance;
    Line = "\t\t"+getdate()+"\t\t"+gettime()+"\n";
    myfile << Line;
    myfile.close();



}
void bankAccount::displaybankTransactions()
{
    ifstream banktransactions;
    banktransactions.open("BankTransactions.txt");
    string line;
    while(getline(banktransactions,line))
    {

        cout << line << endl;

    }

    cout << endl;


}
string bankAccount::getdate()
{
    time_t now = time(0);
    tm * gmtm = gmtime(&now);

    string currenttime = to_string(gmtm->tm_mon) + "/" + to_string(gmtm->tm_mday) + "/" + to_string(gmtm->tm_year);
    return currenttime;
}
