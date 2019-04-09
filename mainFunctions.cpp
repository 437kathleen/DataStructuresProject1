#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void saveFile(string myfile);//
int countLines(string myfile);//count lines in file
void loadFile();//makes hashtable of countlines+1
int getHash(string n);//get hash for table
bool verify(string n, string password);//compare user name with hashtable user names and then the password
void transferFunds(string user1, string user2, int money);//user1 is user loggedin
