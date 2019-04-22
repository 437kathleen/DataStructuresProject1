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
      cout<<"\nWelcome\n";
      do{
        cout<<"\t1) New User \n\t2) Returning User \n\t3) Quit"<<endl;
        getline(cin,ans);
        cout<<endl;
        if(stoi(ans) == 1){
          cout<<"Username: ";
          getline(cin, name);
          cout<<"Password: ";
          getline(cin,password);
          cout<<endl;
          currentUser = B.addUser(name, password);//add a user..return the user for later actions
          if(currentUser != NULL){
            cout<<"Login successful!"<<endl;
            break;
          }else{
            cout<<"Incorrect"<<endl;
          }
        }else if(stoi(ans) == 2){
          cout<<"Username: ";
          getline(cin, name);
          cout<<"Password: ";
          getline(cin,password);
          cout<<endl;
          currentUser = B.login(name,password);
            if(currentUser != NULL){
              cout<<"Login successful!"<<endl;
              break;
            }else{
              cout<<"Incorrect"<<endl;
            }
        }else if(stoi(ans) == 3){
          loginContinue = false;
          cout<<"GOODBYE"<<endl;
        }else{
          cout<<"Invalid choice"<<endl;
        }
      }while(loginContinue == true);
      float money = 0;
      while(loginContinue == true){//ensures that there is a user
        cout<<"Options:\n\t1) Show balance\n\t2) Make a Deposit\n\t3) Make a Withdrawal\n\t4) Show Past History\n\t5) Transfer Money\n\t6) Log out\n";
        getline(cin, ans);
        if(stoi(ans) == 1){
          cout<<"$"<<setprecision(2)<<fixed<<currentUser->getBalance()<<endl;
        }else if(stoi(ans) == 2){
          cout<<"Deposit amount: \n$";
          getline(cin,ans);
          money = stof(ans);
          currentUser->deposit(true, money);//show updated balance if true user...//ask amount and catch negatives
        }else if(stoi(ans) == 3){
          cout<<"Withdrawal amount: \n$";
          getline(cin,ans);
          money = stof(ans);
          currentUser->withdrawal(true, money);//show updated balance if true user...//ask amount and catch negatives
        }else if(stoi(ans) == 4){
          currentUser->printHistory(true);
        }else if(stoi(ans) == 5){//transfer money//implement look up and use deposit and withdrawal to do action
          cout<<"Who would you like to transfer funds to: \n$";
          getline(cin,ans);
          string UserToTransferTo = ans;
          cout<<"How much would you like to transfer: \n$";
          getline(cin,ans);
          money = stof(ans);
          B.transferFunds(currentUser, UserToTransferTo, money);
          //cout<<"transfer"<<endl;
        }else if(stoi(ans) == 6){
          cout<<"GOODBYE"<<endl;
          //loginContinue = false;
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
