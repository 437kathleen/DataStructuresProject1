#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "User.hpp"

using namespace std;

void User::printPublicHistory(){
  if(historyHead == NULL){
    cout<<"No history"<<endl;
  }else{
    transaction *temp = historyHead;
    int i = 1;
    cout<<"HISTORY"<<endl;
    while(temp!=NULL){
      cout<<"\t"<<i<<") "<<temp->name<<endl;
      temp = temp->next;
      i++;
    }
    cout<<"\t\tEND HISTORY"<<endl;
  }
}

void User::printPersonalHistory(){
  if(historyHead == NULL){
    cout<<"No history"<<endl;
  }else{
    transaction *temp = historyHead;
    int i = 1;
    cout<<"HISTORY"<<endl;
    while(temp!=NULL){
      cout<<"\t"<<i<<") "<<temp->name<<"\t$"<<setprecision(2)<<fixed<<temp->amount<<endl;
      temp = temp->next;
      i++;
    }
    cout<<"END HISTORY"<<endl<<endl;
  }
}

void User::loadTransactions(string fileName){
  fstream myfile(fileName);
  if(myfile.is_open()){
    string line,title,item;
    float price = 0;
    //cout<<"load transactions"<<endl;
    while(getline(myfile, line)){
      stringstream ss;
      ss<<line;
      getline(ss,item,',');
      title = item;
      addTransaction(price,title);
    }
  }//else{
    //cout<<"Transactions could not be found"<<endl;
  //}
}

User::User(){
  name = "";
  password = "";
  balance = 0.0;
  debt = 0.0;
  next = NULL;
  historyHead = NULL;
  transactionFile = "";
}

User::User(string n, string p){
  name = n;
  password = p;
  balance = 0.0;
  debt = 0.0;
  historyHead = NULL;
}

User::~User(){

}

string User::getName(){
  return name;
}

string User::getPassword(){
  return password;
}

float User::getBalance(){//decimal
  return this->balance;
}

float User::getDebt(){//demcimal
  return this->debt;
}

void User::deposit(bool isUser){//check for negative amounts
  string ans;//how to narrwo to two decimals;
  cout<<"Deposit amount: \n$";
  getline(cin,ans);
  float money = stof(ans);
  if(money<0){
    cout<<"Illegal Amount"<<endl;
    return;
  }
  addTransaction(money,"Deposit");
  if(isUser == true){//add and show total
    this->balance = getBalance() + money;
    cout<<"New Balance: $"<<setprecision(2)<<fixed<<getBalance()<<endl;
  }else{//just add
    this->balance = getBalance() + money;
  }
}

void User::withdrawal(bool isUser){//check over draw
  string ans;//how to narrwo to two decimals;
  cout<<"Withdrawal amount: \n$";
  getline(cin,ans);
  float money = stof(ans);
  if(money<0){
    cout<<"Illegal Amount"<<endl;
    return;
  }
  addTransaction(money,"Withdrawal");
  if(isUser == true){//add and show total
    this->balance = balance - money;
    cout<<balance<<endl;
  }else{//just add
    this->balance = balance - money;
  }
}

void User::saveTransactions(){
  transaction* transac_trav = this->historyHead;
  std::ofstream save_file(this->name + "_test.txt");
  float amt; // seem to be flipped
  std::string name;

  std::cout << this->name << " has the following info:\n";

  while(transac_trav != NULL){
    amt = transac_trav->amount;
    name = transac_trav->name; // something wrong with ->name, only prints 0's.

    save_file << name << "," << amt << "\n";
    std::cout << name << "," << amt << "\n";

    transac_trav = transac_trav->next;
  }

  save_file.close();
  return;
}

void User::printHistory(bool tf){
  if(tf == true){
    printPersonalHistory();
  }else{
    printPublicHistory();
  }
}

void User::loadUserInfo(string line){
  //File construct will be formatted like so
  // name,password,balance,debt,(file name for transactions)
  //cout<<"load user info - function"<<endl;
  string item;
  stringstream ss;
  ss<<line;
  getline(ss, item,',');
  name = item;
  getline(ss, item,',');
  password = item;
  getline(ss, item,',');
  balance = stof(item);
  getline(ss, item,',');
  debt = stof(item);
  getline(ss, item);
  transactionFile = item;
  loadTransactions(transactionFile);
}

void User::addTransaction(float price, string title){//format will be amount and the name
  //empty list
  transaction *temp = new transaction(price,title);
  //cout<<price<<"\t"<<title<<endl;
  if(historyHead == NULL){
    temp->next = historyHead;
    historyHead = temp;
  }else{//traverse to last element and append on
    transaction *curr = historyHead;
    transaction *prev;
    while(curr!=NULL){//append onto prev
      prev = curr;
      curr = curr->next;
    }//curr == NULL
    prev->next = temp;//add transaction to list
  }
}
