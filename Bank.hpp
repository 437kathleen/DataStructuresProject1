#ifndef BANK_HPP
#define BANK_HPP

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
    int collisions;
    int tableSize;//arbitary

  public:
    Bank(int tableSize);
    ~Bank();

    bool loadFile(string myfile);//take file and read in lines.. pass likes to loadUserInfo of user class

    void saveFile(string myfile);//
    User *login(string name, string password);
    User *getUser(string name);
    void transferFunds(User *currentUser, User *UserToTransferTo);
    void addSavedUser(User *savedUser);//
    User *addUser(string name, string password);
    bool isInTable(string name);
    int findAscii(string name);
    int getHash(string name);
    int numCollisions();
};

#endif
