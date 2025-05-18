#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "account.hpp"
#include "data_acc.hpp"

/*
    

*/

#define PIN_LENGTH 6

void createAccount(){
    std::string fullName, userName, passWord;
    int balance = 0;
    std::vector<int> _PIN;

    std::cout << "Please input your data." << std::endl;
    std::cout << "Full Name\t: ";
    std::getline(std::cin, fullName);

    std::cout << "Username\t: "; 
    std::getline(std::cin, userName);

    std::cout << "Password\t: "; 
    std::getline(std::cin, passWord);

    std::cout << "Your first Balance\t: "; std::cin >> balance;
    std::cin.ignore();

    // // Resizing the length of vector
    // _PIN.resize(PIN_LENGTH);
    // std::cout << "Input your PIN\t: ";
    // for(int i = 0; i < PIN_LENGTH; ++i){
    //     std::cin >> _PIN[i];
    // }

    std::cout << "Input your PIN\t: ";
    for(int i = 0; i < PIN_LENGTH; ++i){
        int digit;
        std::cin >> digit;
        _PIN.push_back(digit);
    }

    std::cin.ignore();
    Account acc(fullName, userName, passWord, balance, _PIN);

    // Create a filename
    std::string filename = fullName;
    std::replace(filename.begin(), filename.end(), ' ', '_');
    filename += ".txt";

    acc.createAccount();

    std::cout << "Account Created!" << std::endl;
}

void checkAccount(){
    std::string full_name;
    std::cout << "Full name of the account owner\t: ";
    std::getline(std::cin , full_name);

    Account acc;
    std::vector<std::string> data = acc.getAccountByFullName(full_name);

    if(!data.empty()){
        std::cout << "Your Name\t\t: " << data[0] << std::endl;
        std::cout << "Your Username\t: " << data[1] << std::endl;
        std::cout << "Your Balance\t: " << std::stoi(data[3]) << std::endl;
    }else{
        std::cout << "Account not found" << std::endl;
    }
}


int main(){
    int menu = 0;
    
    std::cout << "\tWelcome to Bank System\t" << std::endl;
    std::cout << "1. Create Account" << std::endl;
    std::cout << "2. Withdraw" << std::endl;
    std::cout << "3. Deposit" << std::endl;
    std::cout << "4. Check Account" << std::endl;
    std::cout << "5. Get Account Details" << std::endl;
    std::cout << "Please choose the menu\t: "; std::cin >> menu;
    std::cin.ignore();
    

    switch (menu)
    {
    case 1:
        createAccount();
        break;
    case 2:
        std::cout << "Feature not implemented yet!" << std::endl;
        break;
    case 3:
        std::cout << "Feature not implemented yet!" << std::endl;
        break;
    case 4:
        checkAccount();
        break;
    default:
        break;
    }
    
    return 0;
}