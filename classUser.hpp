#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct transaction{
  float amount;
  float title;
  transaction *next;
};

class User{
  private:
    string name;
    string password;
    float balance;
    float debt;
    transaction *historyHead;
    
    void printPublicHistory();
    void printPersonalHistory();
    void loadTransactions(string fileName);

  public:
    User(string name);
    ~User();
    void getName();
    void getBalance(bool tf);
    void getDebt(bool tf);
    void deposit(bool tf, int money);//check for negative amounts
    void withdrawal(bool tf, int money);//check over draw
    void printHistory(bool tf);//call either public or personal
    void loadUserInfo(string line);
    void addTransaction(string line);
};