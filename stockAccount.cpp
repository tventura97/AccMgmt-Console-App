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
#include <iomanip>
using namespace std;
vector <PortfolioItem> Items;                       // creates vector to store portfolio items
int randomnumbercounter = 0;
char LINE[256];


// Constructor. Creates Stock Transactions file. Writes Headers.
stockAccount::stockAccount(double A) : Account(A)
{
    string line = "\nAction\t\tSymbol\t\tShares\t\tPrice\t\tTime\n";
    ofstream myfile;
    myfile.open("Transactions.txt", ios_base::app);
    myfile << line;
    myfile.close();
}
//Destructor
stockAccount::~stockAccount()
{
cout << "Termin";
}

// Opens a random text file and searches the file for a stock symbol (token)
string stockAccount::findstock(string token)
{
    string line;
    srand(randomnumbercounter);
    ifstream StockFile;
    int randno = rand()%4 + 1;
    randomnumbercounter++;
    StockFile.open("stock"+to_string(randno)+".txt"); // open random file
    while(getline(StockFile, line))
    {
        if (line.find(token) != string::npos)         // search for token in file
        {
            found = 1;                                // if found, set found flag to 1
            return line;                              // return line to caller
        }
        else
        {
            found = 0;                                // if line not found, set found flag to 0
        }
    }
    if (found == 0)
    {
        return "not found";                           // if line not found, return 'not found'
    }
}


// Displays stock information requested by user
void stockAccount::displayPrice()
{


    string token;
    cout << "Enter stock symbol for checking price: ";
    cin.getline(LINE,256);                                    // gets stock symbol from user
    cout << LINE << endl;
    token = LINE;
    string stock;
    stock = findstock(token);                        // calls findstock(), passes stock symbol
    if (found == 1)                                  // if found print line and time
    {
      cout << endl << stock + "\t\t\t\t\t\t\t\t\t\t" + gettime() << endl;
        found = 0;                                   // reset flag
    }
    else if (found == 0)                             // if not found, print error
    {
        cout << "Stock not found" << endl;
    }


}


// Buys stock requested by user
void stockAccount::buyStock()
{
    string stock;
    int shares;
    float price;
    float currentprice;
    string currenttime = gettime();

    cout << "Please enter the stock, number of shares, and price." << endl;
    cin.getline(LINE,256);
    cout << LINE << endl;
    stock = getInput(LINE, 0);
    shares = stoi(getInput(LINE, 1));
    price = stof(getInput(LINE, 2));

    if (findstock(stock) == "not found")                            // Checks if stock exists
    {
        cout << "Cannot process transaction. Stock not found." << endl;
        goto buyfinish;
    }

    currentprice = getprice(findstock(stock));                  // if offer price < market price, transaction fails
    if (currentprice > price)
    {
        cout << "Cannot process transaction" << endl;
        cout << "Offer of " << price << " is less than market price of " << currentprice << endl;
        goto buyfinish;
    }
    if (shares*currentprice > cashBalance)
    {

        cout << "Cannot process transaction. Insufficient funds." << endl;           // if insufficient funds, transaction fails
        goto buyfinish;

    }
    cout << "Buying " << shares << " shares of " << stock << " for $" << currentprice << " each." << endl;
    cashBalance -= shares*currentprice;                                         // reduce cashBalance by total cost of purchase
    writeTransaction("Buy", stock, shares,currenttime);                         // calls writeTransaction() to write transaction to file
    updatePortfolio(stock, getcompany(findstock(stock)), shares);               // calls updatePortfolio() to update portfolio (vector<PortfolioItem> Items)




buyfinish:
    {
        1+1;
    }
}

// sells stocks. Practically the same as the buyStock() function
void stockAccount::sellStock()
{
    string stock;
    int shares;
    float price;
    string currenttime = gettime();
    float currentprice = getprice(findstock(stock));
    int foundsymbol = 0;
    cout << "Please enter the stock, number of shares, and selling price" << endl;
    cin.getline(LINE,256);
    cout << LINE << endl;
    stock = getInput(LINE, 0);
    shares = stoi(getInput(LINE, 1));
    price = stof(getInput(LINE, 2));

    for (int i = 0; i < Items.size(); i++)
    {
        if (getsymbol(stock)==Items[i].Symbol)              // Checks if user owns stock they want to sell
        {
            foundsymbol = 1;
        }
    }
    if (foundsymbol != 1)
    {
        cout << "Cannot process transaction. Stock not owned." << endl;
        goto sellfinish;
    }

    if (price > currentprice)
    {
        cout << "Cannot process transaction." << endl;
        cout << "Selling price of " << price << " is greater than market price of " << currentprice << endl;
    }
    if (price <= currentprice)
    {
    cout << "Selling " << shares << " shares of " << getsymbol(stock) << " for $" << currentprice << " each." << endl;
    cashBalance += shares*currentprice;
    writeTransaction("Sell", stock, shares,currenttime);
    updatePortfolio(stock, getcompany(findstock(stock)), -shares);

    }

sellfinish:
    {
        1+1;
    }


}
// parses inputline
string stockAccount::getInput(string line, int a)
{
    string delim = " ";
    vector <string> tokens;
    tokens.clear();
    for (int i = 0; i<3; i++)
    {
        if (i == 2)
        {
            line = line.substr(line.rfind(delim)+1,string::npos);
            tokens.push_back(line);
        }

    tokens.push_back(line.substr(0,line.find(delim)));
    line = line.substr(line.find(delim)+1, string::npos);
    }
return tokens[a];


}
//Parses a line from the text files and returns the stock's symbol
string stockAccount::getsymbol(string line)
{
    string delim = "\t";
    vector <string> tokens;
    tokens.clear();
    for (int i = 0; i<3; i++)
    {
        if (i == 2)
        {
            line = line.substr(line.rfind(delim)+1,string::npos);
            tokens.push_back(line);
        }

    tokens.push_back(line.substr(0,line.find(delim)));
    line = line.substr(line.find(delim)+1, string::npos);
    }
return tokens[0];


}

//parses a line from the text file and returns the stock's company name
string stockAccount::getcompany(string line)
{
    string delim = "\t";
    vector <string> tokens;
    tokens.clear();
    for (int i = 0; i<3; i++)
    {
        if (i == 2)
        {
            line = line.substr(line.rfind(delim)+1,string::npos);
            tokens.push_back(line);
        }

        tokens.push_back(line.substr(0,line.find(delim)));
        line = line.substr(line.find(delim)+1, string::npos);
    }
return tokens[1];


}

// parses line from stock file and returns stock's price
float stockAccount::getprice(string line)
{

    string delim = "\t";
    vector <string> tokens;
    tokens.clear();
    for (int i = 0; i<3; i++)
    {
        if (i == 2)
        {
            line = line.substr(line.rfind(delim)+1,string::npos);
            tokens.push_back(line);
        }

        tokens.push_back(line.substr(0,line.find(delim)));
        line = line.substr(line.find(delim)+1, string::npos);
    }
return stof(tokens[2]);

}

//writes transactions to file
void stockAccount::writeTransaction(string action, string stock, int shares, string currenttime)
{

    string line = findstock(stock);
    float price = getprice(line);
    string company = getcompany(line);
    string symbol = getsymbol(line);

    ofstream myfile;
    myfile.open("Transactions.txt", ios_base::app);
    string Line = action+"\t\t"+symbol+"\t\t";
    myfile << Line;
    myfile << fixed << setprecision(2) << shares;
    Line = "\t\t";
    myfile << Line;
    myfile << fixed << setprecision(2) << price;
    Line = "\t\t"+currenttime+"\n";
    myfile << Line;
    myfile.close();





}

//prints Transactions.txt file to the console
void stockAccount::displayTransactions()
{
    ifstream Transactionfile;
    Transactionfile.open("Transactions.txt");
    string line;
    while (getline(Transactionfile,line))
    {

        cout << line << endl;

    }
}


// updates portfolio vector
void stockAccount::updatePortfolio(string symbol, string company, int number)
{
        bool present;
        PortfolioItem newItem;
        newItem.CompanyName = company;
        newItem.Symbol = symbol;
        newItem.NumShares = number;

        for (int i = 0; i< Items.size(); i++)
        {
            if (Items[i].Symbol == symbol)
            {
                present = true;
                if (Items[i].NumShares + number >= 0)
                {
                    if (Items[i].NumShares + number == 0)
                    {
                        Items[i].NumShares += number;
                        cout << "Stock " << Items[i].Symbol << " no longer owned. All shares sold." << endl;
                        Items.erase(Items.begin()+i);
                    }
                    Items[i].NumShares += number;

                }
                else if (Items[i].NumShares + number < 0)
                {
                    cout << "Cannot process transaction. Insufficient Shares." << endl;
                }

            }
        }

        if (present != true)
        {
            Items.push_back(newItem);
        }
        sortStocks();

}

// prints portfolio vector
void stockAccount::displayCurrentPortfolio()
{
    printf("\nCash balance = $%.2f\n\n", cashBalance);
    cout << "Symbol\t\tCompany\t\t\t\t\tNumber\t\tPrice\t\tTotal" << endl;
    double total = 0;
    string tab;
    for (int i = 0; i < Items.size(); i++)
    {
        if (Items[i].CompanyName.length() > 23) //Fixes formatting
        {
            tab = "\t\t";

        }
        else if (Items[i].CompanyName.length() <= 23)
        {
            tab = "\t\t\t";
        }
        cout << Items[i].Symbol+"\t\t"+Items[i].CompanyName+tab+to_string(Items[i].NumShares)+"\t\t$" << getprice(findstock(Items[i].Symbol))<< "\t\t$";
        cout << fixed << setprecision(2) << getprice(findstock(Items[i].Symbol))*Items[i].NumShares  << endl;
        total +=getprice(findstock(Items[i].Symbol))*Items[i].NumShares;
    }
    printf("\nTotal portfolio value is: %.2f\n\n", total+cashBalance);

}

//gets current system time. returns as a string.
string stockAccount::gettime()
{
    time_t now = time(0);
    tm * gmtm = gmtime(&now);

    string currenttime = to_string(gmtm->tm_hour) + ":" + to_string(gmtm->tm_min) + ":" + to_string(gmtm->tm_sec);
    return currenttime;

}

//sorts portfolio by symbol alphabetically. Uses insertion sort.
void stockAccount::sortStocks()
{
    PortfolioItem SMALLEST;
    SMALLEST.Symbol = "ZZZZ";
    PortfolioItem TEMP;
    int place = 0;                                      // track current location in vector
    int smallestindex;
    int charcounter = 0;
    int flag = 0;
    for (int i = 0; i < Items.size(); i ++)
    {
        SMALLEST.Symbol = "ZZZZ";
        for (int j = place; j < Items.size(); j++)
        {
            charcounter = 0;                            // reset character counter
           while(charcounter < 4)
           {
               if (int(Items[j].Symbol[charcounter]) == int(SMALLEST.Symbol[charcounter]))
               {
                   charcounter++;                       // If characters are the same, compare next character
               }
               else if (int(Items[j].Symbol[charcounter]) < int(SMALLEST.Symbol[charcounter]))
               {
                    SMALLEST = Items[j];                // Smallest member is reassigned
                    smallestindex = j;                 // Store location of smallest member
                    flag = 1;
                    break;

               }
               else if (int(Items[j].Symbol[charcounter]) > int(SMALLEST.Symbol[charcounter]))
               {
                   break;

               }

           }
        }
        if (flag == 1)
        {
            TEMP = Items[place];                        // Swap
            Items[place] = SMALLEST;
            Items[smallestindex] = TEMP;
            flag = 0;                                   // reset flag
        }
        place ++;


    }


}
