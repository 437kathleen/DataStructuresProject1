#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "User.hpp"

using namespace std;

class Bank{
  private:
    User** account;
    int numAccounts;//unnecessary
    int collisions;//check the efficiency 
    int tableSize;//arbitrarily set
  public:
    Bank(int lines);
    ~Bank();

    //int countLines(string myfile);//count lines in file
    bool loadFile(string myfile);//makes hashtable
  
    void saveFile(string myfile);//****************need to implement
  
    void addSavedUser(User *savedUser);
    void addUser(string name);
    bool isInTable(string name);
    int findAscii(string name);
    int getHash(int value);
    int numCollisions();
    
};

Bank::Bank(int tableSize){
  collisions = 0;
  //tableSize = 100;
  //this->numAccounts = tableSize;
  this->tableSize = tableSize;
  account = new User*[tableSize];
  for(int i=0;i<tableSize;i++){
    account[i] = NULL;
  }
}

Bank::~Bank(){
  for(int i = 0; i < tableSize; i++){
    User *store = account[i];
    Node *temp = NULL;
    while(store!=NULL){
      temp = store;
      store = store->next;
      delete temp;
    }
    //delete hashTable[i];
  }
}//delete

bool Bank::loadFile(string myfile){
  fstream accountfile(myfile);
  if(accountfile.is_open() == true){
    //int count = numAccounts;
    string line, item, name, password;
    while(!accountfile.eof){
      getline(accountfile, line);
      User *newUser = new User;
      newUser.loadUserInfo(line);
      addSavedUser(newUser);
    }
    accountfile.close();
  }else{
    cout<<"File not found"<<endl;
  }
}

void Bank::saveFile(string myfile){//**************not finished need to be changed

}

void Bank::addSavedUser(User *savedUser){
  int index = getHash(savedUser->name);
  if(account[index]!=NULL){///moniter collisions
    collisions++;
  }
  savedUser->next = account[index];//push to front
  account[index] = savedUser;
}

void Bank::addUser(string name, string password){
  if(isInTable(value)==false){
      // Use the hash function on the key to get the index/slot,
      int index = getHash(value);
      if(account[index]!=NULL){///moniter collisions
        collisions++;
      }
      // create a new user with the name and password and insert it in this index's list
      User *newUser = new User;
      newUser->name = name;
      newUser->password = password;
      newUser->balance = 0.0;
      newUser->debt = 0.0;
      newUser->historyHead = NULL;
      newUser->next = account[index];//push to front
      account[index] = newUser;
  }else{
    cout<<"Invalid username"<<endl;
  }
}

bool Bank::isInTable(string name){
  //find ascii to convert name to
  int index = getHash(name);
  User *tempUser = account[index];
  while(tempUser!=NULL){
    if((tempUser->name).compare(name)==0){
      return true;
    }
    tempUser = tempUser->next;
  }
return false;
}

int Bank::findAscii(string name){//return ascii value
  int i = 0;
  int sum = 0;
  while(name[i] != '\0'){
    sum = sum + int(name[i]);
    i++;
  }
  cout<<"Ascii: "<< sum << endl;
  return sum;
}

int Bank::getHash(string name){//returns index
  int value = findAscii(name);
  int index = value%100;
  cout<<"name: "<<name<<"  index: "<< index<< endl;
  return index;
}

int Bank::numCollisions(){
  cout<<"collisions: "<<collisions<<endl;
  return collisions;
}
