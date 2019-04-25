#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bank.hpp"
#include "User.hpp"

using namespace std;


Bank::Bank(int tableSize){
  collisions = 0;
  this->tableSize = tableSize;
  account = new User*[tableSize];
  for(int i=0;i<tableSize;i++){
    account[i] = NULL;
  }
}

Bank::~Bank(){
  for(int i = 0; i < tableSize; i++){
    User *store = account[i];
    User *temp = NULL;
    while(store!=NULL){
      temp = store;
      store = store->next;
      delete temp;
    }
    //delete hashTable[i];
  }
}

bool Bank::loadFile(string myfile){
  bool loaded = false;
  fstream accountfile(myfile);
  if(accountfile.is_open() == true){
    //int count = numAccounts;
    string line, item, name, password;
    while(getline(accountfile, line)){
      User *newUser = new User;
      newUser->loadUserInfo(line);//call function
      addSavedUser(newUser);//add user to hashtable
    }
    accountfile.close();
    loaded = true;
  }else{
    cout<<"File not found"<<endl;
  }
  return loaded;
}

void Bank::saveFile(string myfile){
  ofstream save_file(myfile);
  string name;
  if (!save_file){
    cout << "cannot open file\n";
    return;
  }
  for (int i = 0;i<tableSize; i++){
    User *temp = account[i];
    while (temp!=NULL){
      name = temp->getName();
      save_file << name << "," << temp->getPassword() << "," << temp->getBalance() << "," << temp->getTransactionFileName() << "\n";
      temp->saveTransactions();
      temp = temp->next;
    }
  }
  return;//overwrite the file
}

User *Bank::login(string name, string password){
  User *temp = getUser(name);
  if(temp!=NULL){
    //check passwords match
    if((temp->getPassword()).compare(password)==0){
      return temp;
    }
  }
  cout<<"ERROR"<<endl;
  return NULL;
}

User *Bank::getUser(string name){
  //find hash look for user and return
  if(isInTable(name)==true){
    int index = getHash(name);
    User *temp = account[index];
    while(temp!=NULL){
      if((temp->getName()).compare(name)==0){
        return temp;
      }
      temp = temp->next;
    }
  }else{
    cout<<"ERROR"<<endl;
    return NULL;
  }
}

void Bank::transferFunds(User *currentUser, User *UserToTransferTo){
  string ans;
  cout<<"How much would you like to transfer: \n$";
  getline(cin,ans);
  float money = stof(ans);
  if((currentUser->getName()).compare(UserToTransferTo->getName()) == 0){//user transfers to themselves
    currentUser->withdrawal(money);
    currentUser->deposit(true,money);
    return;
  }
  if(UserToTransferTo != NULL){
    bool enoughMoney = currentUser->withdrawal(money);//take money from user
    if(enoughMoney == true){
      UserToTransferTo->deposit(false,money);
    }
  }else{
    cout<<"User not found"<<endl;
  }
}

void Bank::addSavedUser(User *savedUser){
  int index = getHash(savedUser->getName());
  if(account[index]!=NULL){///moniter collisions
    collisions++;
  }
  savedUser->next = account[index];//push to front
  account[index] = savedUser;
}

User *Bank::addUser(string name, string password){
  User *newUser = new User(name, password);
  if(isInTable(name)==false){
      // Use the hash function on the key to get the index/slot,
      int index = getHash(name);
      if(account[index]!=NULL){///moniter collisions
        collisions++;
      }
      newUser->next = account[index];//push to front
      account[index] = newUser;
  }else{
    cout<<"Username taken"<<endl;
    newUser = NULL;
  }
  return newUser;
}

bool Bank::isInTable(string name){
  //find ascii to convert name to
  int index = getHash(name);
  User *tempUser = account[index];
  while(tempUser!=NULL){
    if((tempUser->getName()).compare(name)==0){
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
  return sum;
}

int Bank::getHash(string name){//returns index
  int value = findAscii(name);
  int index = value%100;
  return index;
}

int Bank::numCollisions(){
  cout<<"collisions: "<<collisions<<endl;
  return collisions;
}
