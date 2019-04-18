

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct transaction{
  float amount;
  string name;
  transaction *next;
  transaction(float a, string n){
    amount = a;
    name = n;
    next = NULL;
  }
};

class User{
  private:
    string name;
    string password;
    float balance;
    float debt;

    string transactionFile;
    transaction *historyHead;

    void printPublicHistory();
    void printPersonalHistory();
    void loadTransactions(string fileName);

  public:
    User *next;
    User();
    User(string n, string p);

    ~User();


    string getName();

    float getBalance();
    float getDebt();
    void deposit(bool isUser);//check for negative amounts
    void withdrawal(bool isUser);//check over draw

    void saveTransactions();

    void printHistory(bool isUser);//call either public or personal
    void loadUserInfo(string line);
    void addTransaction(float price, string title);
};

#endif
