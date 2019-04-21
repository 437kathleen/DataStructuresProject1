#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
//#include "Bank.hpp"
#include "User.hpp"
#include "Bank.hpp"

/*

cd Desktop\2270\Bank
g++ -std=c++11 bank.cpp bank.hpp main.cpp user.hpp user.cpp -o banking

*/
using namespace std;

void transferFunds(string user1, string user2, int money);//user1 is user loggedin

int main(int argc, char *argv[]){
  Bank B(100);//parameter arbitary
  //int count = countLines(argv[2]);
  string ans;
  string rw_filename; // stores read/ write filename for use when saving
  B.numCollisions();
  cout<<"Load bank file: "<<endl;
  getline(cin,rw_filename);
  bool loaded = B.loadFile(rw_filename);///read in users and assign info appropriately
  if(loaded == true){//loaded file or empty file
    string name, password;
    bool loginContinue = true;
    User *currentUser;
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
        break;
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
        //currentUser = B.getUser(name, password);//add a user..return the user for later actions
        //cout<<currentUser->getName()<<endl;
      }else if(stoi(ans) == 3){
        cout<<"GOODBYE"<<endl;
        loginContinue = false;
      }else{
        cout<<"Invalid choice"<<endl;
      }
    }while(loginContinue == true);

    while(loginContinue == true){//ensures that there is a user
      cout<<"Options:\n\t1) Show balance\n\t2) Show Debt\n\t3) Make a Deposit\n\t4) Make a Withdrawal\n\t5) Show Past History\n\t6) Transfer Money\n\t7) Quit\n";
      getline(cin, ans);
      if(stoi(ans) == 1){
        cout<<"$"<<setprecision(2)<<fixed<<currentUser->getBalance()<<endl;
      }else if(stoi(ans) == 2){
        cout<<"-$"<<setprecision(2)<<fixed<<currentUser->getDebt()<<endl;
      }else if(stoi(ans) == 3){
        currentUser->deposit(true);//show updated balance if true user...//ask amount and catch negatives
      }else if(stoi(ans) == 4){
        currentUser->withdrawal(true);//show updated balance if true user...//ask amount and catch negatives
      }else if(stoi(ans) == 5){
        currentUser->printHistory(true);
      }else if(stoi(ans) == 6){//transfer money//implement look up and use deposit and withdrawal to do action
        cout<<"transfer"<<endl;
      }else if(stoi(ans) == 7){
        cout<<"GOODBYE"<<endl;
        loginContinue = false;
      }else{
        cout<<"Invalid choice"<<endl;
      }
    }
    B.saveFile(rw_filename);
    cout<<"System shutdown"<<endl;
  }else{
    //no history file
    cout<<"ERROR::GOODBYE"<<endl;
  }
}
