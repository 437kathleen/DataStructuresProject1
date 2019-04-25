#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "User.hpp"
#include "Bank.hpp"

/*

cd Desktop\2270\Bank
g++ -std=c++11 bank.cpp bank.hpp main.cpp user.hpp user.cpp -o banking

*/

using namespace std;

int main(int argc, char *argv[]){
  Bank B(100);//parameter arbitary
  //int count = countLines(argv[2]);
  string ans;
  B.numCollisions();
  cout<<"Load bank file: "<<endl;
  getline(cin,ans);
  string fileName = ans;
  bool loaded = B.loadFile(fileName);///read in users and assign info appropriately
  if(loaded == true){//loaded file or empty file
    string name, password;
    bool loginContinue = true;
    User *currentUser;
    //bool shutDown = false;
    do{
      cout<<"\nWelcome";
      do{
        cout<<"\n\t1) New User \n\t2) Returning User \n\t3) Quit"<<endl;
        getline(cin,ans);
        if(ans.compare("1") == 0){
          cout<<"Username: ";
          getline(cin, name);
          cout<<"Password: ";
          getline(cin,password);
          cout<<endl;
          currentUser = B.addUser(name, password);//add a user..return the user for later actions
          if(currentUser != NULL){
            break;
          }
        }else if(ans.compare("2") == 0){
          cout<<"Username: ";
          getline(cin, name);
          cout<<"Password: ";
          getline(cin,password);
          cout<<endl;
          currentUser = B.login(name,password);
            if(currentUser != NULL){
              break;
            }
        }else if(ans.compare("3") == 0){
          loginContinue = false;
        }else{
          cout<<"Invalid choice"<<endl;
        }
      }while(loginContinue == true);


      float money = 0;
      if(loginContinue == true) cout<<"Welcome, "<< currentUser->getName()<<"!"<<endl;
      while(loginContinue == true){//ensures that there is a user
        cout<<"\nOptions:\n\t1) Show balance\n\t2) Make a Deposit\n\t3) Make a Withdrawal\n\t4) Show Past History\n\t5) Look up user\n\t6) Log out\n";
        getline(cin, ans);
        if(ans.compare("1") == 0){
          cout<<"Current Balance: $"<<setprecision(2)<<fixed<<currentUser->getBalance()<<endl;
        }else if(ans.compare("2") == 0){
          cout<<"Deposit amount: \n$";
          getline(cin,ans);
          money = stof(ans);
          currentUser->deposit(true, money);//show updated balance if true user...//ask amount and catch negatives
        }else if(ans.compare("3") == 0){
          cout<<"Withdrawal amount: \n$";
          getline(cin,ans);
          money = stof(ans);
          currentUser->withdrawal(money);//show updated balance if true user...//ask amount and catch negatives
        }else if(ans.compare("4") == 0){
          currentUser->printHistory(true);
        }else if(ans.compare("5") == 0){//transfer money//implement look up and use deposit and withdrawal to do action
          cout<<"Search: "<<endl;
          getline(cin,ans);
          User* searchUser = B.getUser(ans);
          if(searchUser != NULL){
            cout<<"User found!"<<endl;
            while(loginContinue == true){
              cout<<"\nOptions:\n\t1) Transfer Funds\n\t2) View History\n\t3) Go Back\n";
              getline(cin,ans);
              if(ans.compare("1") == 0){
                B.transferFunds(currentUser, searchUser);
              }else if(ans.compare("2") == 0){
                searchUser->printHistory(false);
              }else{
                break;
              }
            }
          }
        }else if(ans.compare("6") == 0){
          cout<<"Goodbye, "<<currentUser->getName()<<endl;
          break;
        }else{
          cout<<"Invalid choice"<<endl;
        }
      }
      B.saveFile(fileName);
    }while(loginContinue == true);
    cout<<"System shutdown"<<endl;
  }else{
    //no history file
    cout<<"ERROR::GOODBYE"<<endl;
  }
}
