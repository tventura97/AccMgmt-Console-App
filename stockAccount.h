#ifndef STOCKACCOUNT_H_INCLUDED
#define STOCKACCOUNT_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
class stockAccount : public Account{
protected:
int found;
int firstitem = 0;
string paths[4] ={"stock1.txt", "stock2.txt", "stock3.txt", "stock4.txt"};
public:
    stockAccount(double A);
    ~stockAccount();
    void displayPrice();
    void buyStock();
    void displayTransactions();
    void sellStock();
    void displayCurrentPortfolio();
    void updatePortfolio(string symbol, string company, int number);
    float getprice(string line);
    string getsymbol(string line);
    string getcompany(string line);
    string findstock(string);
    void print(string);
    void writeTransaction(string action, string stock, int shares, string time);
    void sortStocks();
    string gettime();
    void sortStocks2();
    string getInput(string line, int i);


};

struct PortfolioItem
{
    string Symbol;
    string CompanyName;
    int NumShares;


};
#endif // STOCKACCOUNT_H_INCLUDED
