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
    cout<<"END HISTORY"<<endl;
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
      price = stof(item);
      getline(ss,item);
      title = item;
      addTransaction(price,title);
    }
  }
}

User::User(){
  name = "";
  password = "";
  balance = 0.0;
  next = NULL;
  historyHead = NULL;
  transactionFile = "";
}

User::User(string n, string p){
  name = n;
  password = p;
  balance = 0.0;
  historyHead = NULL;
  transactionFile = n + ".txt";
}

User::~User(){
  transaction *temp = historyHead;
  while(historyHead != NULL){
    temp = historyHead;
    historyHead = historyHead->next;
    delete temp;
  }
  //delete users
}

string User::getName(){
  return name;
}

string User::getPassword(){
  return password;
}

string User::getTransactionFileName(){
  return transactionFile;
}

float User::getBalance(){//decimal
  return this->balance;
}

void User::deposit(bool isUser, float money){//check for negative amounts
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

bool User::withdrawal(float money){//check over draw
  if(money<0 || money > getBalance()){
    cout<<"Illegal Amount"<<endl;
    return false;
  }
  addTransaction(money,"Withdrawal");
  this->balance = balance - money;
  cout<<"New Balance: "<<balance<<endl;
  return true;
}

void User::saveTransactions(){
  ofstream myfile(transactionFile);
  if(myfile.is_open()){
    transaction *temp = historyHead;
    while(temp!=NULL){
      myfile << temp->amount <<","<< temp->name << endl;
      //cout << getName() << temp->amount <<","<< temp->name << endl;
      temp = temp->next;
    }
    return;
  }
  //cout<<"Cannot open file\n";
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
  // name,password,balance,(file name for transactions)
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
