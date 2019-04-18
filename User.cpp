//Functions
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
    int i = 0;
    cout<<"HISTORY"<<endl;
    while(temp!=NULL){
      cout<<"\t"<<i<<": "<<temp->name<<endl;
      temp = temp->next;
    }
    cout<<"\t\tEND HISTORY"<<endl;
  }
}

void User::printPersonalHistory(){
  if(historyHead == NULL){
    cout<<"No history"<<endl;
  }else{
    transaction *temp = historyHead;
    int i = 0;
    cout<<"HISTORY"<<endl;
    while(temp!=NULL){
      cout<<"\t"<<setw(30)<<temp->name<<"$"<<setprecision(2)<<fixed<<temp->amount<<endl;
      temp = temp->next;
    }
    cout<<"\t\tEND HISTORY"<<endl;
  }
}

void User::loadTransactions(string fileName){
  fstream myfile(fileName);
  if(myfile.is_open()){
    string line;
    while(!myfile.eof()){
      getline(myfile, line);
      addTransaction(line);
    }
  }else{
    //cout<<"Transactions could not be found"<<endl;
  }
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

void User::getBalance(bool isUser){

}

void User::getDebt(bool isUser){

}

void User::deposit(bool isUser){//check for negative amounts

}

void User::withdrawal(bool isUser){//check over draw

}

void User::saveTransactions(){

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

void User::addTransaction(string line){
  //empty list
  stringstream ss;
  ss<<line;
  string item;
  if(historyHead == NULL){
    transaction *temp;
    getline(ss, item,',');
    temp->name = item;
    getline(ss, item);
    temp->amount = stof(item);
    historyHead = temp;
  }else{//traverse to last element and append on
    transaction *temp = historyHead;
    transaction *prev;
    transaction *curr;
    while(temp!=NULL){//append onto prev
      prev = temp;
      temp = temp->next;
    }//temp == NULL
    getline(ss, item,',');
    curr->name = item;
    getline(ss, item);
    curr->amount = stof(item);
    prev->next = curr;//add transaction to list
  }
}
