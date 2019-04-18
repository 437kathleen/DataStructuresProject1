//Functions
#include <iostream>
#include <fstream>
//#include <sstream>
#include <string>

using namespace std;

void User::loadTransactions(string fileName){
  fstream myfile(fileName);
  if(myfile.is_open()){
    string line;
    while(!myfile.eof()){
      getline(myfile, line);
      addTransaction(line);
    }
  }else{
    cout<<"File could not be found"<<endl;
  }
}

void User::printPublicHistory(){
  if(historyHead == NULL){
    cout<<"No history"<<endl;
  }else{
    transaction *temp = historyHead;
    int i = 0;
    cout<<"HISTORY"<<endl;
    while(temp!=NULL){
      cout<<"\t"<<i<<": "<<temp.name<<endl;
      temp = temp->next;
    }
    cout<<"END HISTORY"<<endl;
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
  if(historyHead == NULL){
    transaction *temp;
    getline(ss, item,',');
    temp.name = item;
    getline(ss, item);
    temp.amount = stof(item);
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
    curr.name = item;
    getline(ss, item);
    curr.amount = stof(item);
    prev->next = curr;//add transaction to list
  }
}
