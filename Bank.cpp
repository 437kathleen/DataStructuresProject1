#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bank.hpp"
#include "User.hpp"

using namespace std;


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
    User *temp = NULL;
    while(store!=NULL){
      temp = store;
      store = store->next;
      delete temp;
    }
    //delete hashTable[i];
  }
}//delete

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
  std::cout << "Saving file under name: " << myfile << "\n";
  std::ofstream save_file(myfile); // careful, this overwrites the file!!
  std::string name, pswd;
  float bal, debt;
  User* tmp_trav = NULL;

  if (!save_file){
    std::cout << "cannot open file\n";
    return;
  }

  for (int i =0;i<tableSize; i++){ // for every element in the HT
    if (account[i]!=NULL){ //  if the element exists (is a valid user)
      tmp_trav = account[i];
      while (tmp_trav != NULL){ // go throught linked list printing the names
        name = tmp_trav->getName();
        debt = tmp_trav->getDebt();
        bal = tmp_trav->getBalance();
        pswd = tmp_trav->getPassword();
        save_file << name << "," << pswd << "," << bal << "," << debt << "," << name << ".txt\n";
        std::cout << name << "," << pswd << "," << bal << "," << debt << "," << name << ".txt\n";
        
        tmp_trav = tmp_trav->next;
      }
    }
  }

  return;
  //overwrite the file
}

User *Bank::login(string name, string password){
  User *temp = getUser(name);
  if(temp!=NULL){
    //check passwords match
    if((temp->getPassword()).compare(password)==0){
      return temp;
    }
  }
  return temp;
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
    cout<<"User does not exist"<<endl;
    return NULL;
  }

}

void Bank::addSavedUser(User *savedUser){
  int index = getHash(savedUser->getName());
  if(account[index]!=NULL){///moniter collisions
    collisions++;
  }
  //cout<<"adding a saved user"<<endl;
  savedUser->next = account[index];//push to front
  account[index] = savedUser;
  //cout<<"here"<<endl;
}

User *Bank::addUser(string name, string password){
  User *newUser = new User(name, password);
  if(isInTable(name)==false){
      // Use the hash function on the key to get the index/slot,
      int index = getHash(name);
      if(account[index]!=NULL){///moniter collisions
        collisions++;
      }
      // create a new user with the name and password and insert it in this index's list
      //User *newUser = new User;
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
  //cout<<"Ascii: "<< sum << endl;
  return sum;
}

int Bank::getHash(string name){//returns index
  int value = findAscii(name);
  int index = value%100;
  //cout<<"name: "<<name<<"  index: "<< index<< endl;
  return index;
}

int Bank::numCollisions(){
  cout<<"collisions: "<<collisions<<endl;
  return collisions;
}
