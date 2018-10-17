//#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "stockAccount.h"
#include "bankAccount.h"
using namespace std;

int main()
{
    char LINE[256];
    bankAccount NewAccount(100000);
    int input;
    while(input != 3)                                                   // menu
    {   cout << "\nWelcome to the Account Management System" << endl;
        start:
        cout << "Please select an account to access" << endl;
        cout << "\t1. Stock Portfolio Account" << endl;
        cout << "\t2. Bank Account" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tYour selection:  ";
        cin.getline(LINE, 256);
        input = atoi(LINE);
        cout << input << endl;
        /*if (cin.fail() || input > 3 || input < 1)
        {
            cin.clear();
            cin.ignore(999999999, '\n');
            cout << "Invalid selection" << endl;
        }*/
        while (input != 6)
        {
            switch(input)
            {
            case 1:
                {
                        int selection;
                            start2:
                            cout << "\nPlease select an option" << endl;
                            cout << "\t1. Display current price for a stock symbol" << endl;
                            cout << "\t2. Buy stock" << endl;
                            cout << "\t3. Sell stock" << endl;
                            cout << "\t4. Display current portfolio" << endl;
                            cout << "\t5. Display transactions history" << endl;
                            cout << "\t6. Return to main menu" << endl;
                            cout << "\tYour selection: ";
                            cin.getline(LINE, 256);
                            selection = atoi(LINE);
                            cout << selection << endl;
                            switch(selection)
                            {
                                case 1: NewAccount.displayPrice();
                                        goto start2;

                                case 2: NewAccount.buyStock();
                                        goto start2;

                                case 3: NewAccount.sellStock();
                                        goto start2;

                                case 4: NewAccount.displayCurrentPortfolio();
                                        goto start2;

                                case 5: NewAccount.displayTransactions();
                                        goto start2;

                                case 6: goto start;
                        }
                }
            case 2:
                {
                    int selection;
                    start3:
                    cout << "Please select an option" << endl;
                    cout << "\t1. View account balance" << endl;
                    cout << "\t2. Deposit money" << endl;
                    cout << "\t3. Withdraw money" << endl;
                    cout << "\t4. Display transactions history" << endl;
                    cout << "\t5. Return to previous menu" << endl;
                    cout << "\tYour selection: ";
                    cin.getline(LINE, 256);
                    selection = atoi(LINE);
                    cout << selection << endl;

                    switch(selection)
                    {
                        case 1: NewAccount.displayCurrentPortfolio();
                                goto start3;
                        case 2: NewAccount.deposit();
                                goto start3;
                        case 3: NewAccount.withdraw();
                                goto start3;
                        case 4: NewAccount.displaybankTransactions();
                                goto start3;
                        case 5: goto start;
                    }
                }
            case 3: goto exit;
        }
    }
    }
exit:
return 0;
}
