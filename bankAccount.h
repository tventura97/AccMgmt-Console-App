#ifndef BANKACCOUNT_H_INCLUDED
#define BANKACCOUNT_H_INCLUDED

class bankAccount: public stockAccount
{
protected:

public:
    bankAccount(double A);
   ~bankAccount();
    void deposit();
    void withdraw();
    void displaybankTransactions();
    void writebankTransaction(string action, double amount);
    string getdate();




};

#endif // BANKACCOUNT_H_INCLUDED
