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
    int numAccounts;
  public:
    Bank(int lines);
    ~Bank();

    //int countLines(string myfile);//count lines in file
    bool loadFile(string myfile);//makes hashtable of countlines+1
    void saveFile(string myfile);//
};

Bank::Bank(int numLines, vector<string> file){
  this->numAccounts = numLines;
  account = new User*[numLines];
  for(int i=0;i<numAccounts;i++){
    account[i] = NULL;
  }
}

bool Bank::loadFile(string myfile){
  fstream accounts(myfile);
  if(accounts.is_open() == true){
    int count = numAccounts;
    while(!account.eof){
      getline(accounts,line);
      account[count].loadUserInfo(line);
      count--;
    }
    accounts.close();
  }else{
    cout<<"File not found"<<endl;
  }
}

void Bank::saveFile(string myfile){

}

void Bank::addUser(string name){//**************not finished need to be changed
  //cout<<value<<endl;
  if(isInTable(value)==false){
      // Use the hash function on the key to get the index/slot,
      int index = getHash(value);
      // create a new node with the key and insert it in this slot's list
      Node *Node1 = new Node;
      Node1->key = value;
      Node1->next = hashTable[index];//push to front
      hashTable[index] = Node1;
  }
}
