#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "data_acc.hpp"
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
/* 
    User Data : 
    1. Full Name
    2. Username
    3. Password
    4. Balance
    5. PIN
*/

class Account{
    private:
        std::string fullName;
        std::string userName;
        std::string passWord;
        int _balance = 0;
        std::vector<int> _PIN;


        bool validatingData(const std::string& full_name){
            std::string filename = generateFilename(full_name);
            std::vector<std::string> data = getFile(filename, "database");
            // If file has at least one line, return file exists
            return !data.empty();
        }

        bool validatingFullName(const std::string& full_name){
            return (full_name == fullName);
        }

        // Validating Username if username has been reocorded
        bool validateUsername(std::string username){
            return (username == userName);
        }

        // Validating new password with old password
        bool validatePassword(std::string new_password){        
            return (new_password != passWord);
        }

        // Validating if the new pin has a same value with the old pin.
        bool validatePIN(std::vector<int> new_pin){
            return (new_pin.size() == _PIN.size() && new_pin != _PIN);
        }
        
        // Check if the account has enough balance
        bool checkBalance(int amount){
            return (amount <= _balance);
        }

        std::string generateFilename(const std::string& full_name){
            std::string filename = full_name;
            std::replace(filename.begin(), filename.end(), ' ', '_');
            filename += ".txt";

            return filename;
        }

    public:

        /* CONSTRUCTOR */
        Account(const std::string& full_name, const std::string& username, const std::string& password, int balance, std::vector<int> PIN) : fullName(full_name), userName(username), passWord(password), _balance(balance), _PIN(PIN){}

        Account() : fullName(""), userName(""), passWord(""), _balance(0), _PIN(){}

        /* 

            MAIN FUNCTION : 
            1. createAccount()
            FUNCTIONS : 
            1. getAccountByFullName(std::string) -> return : void;
            2. getAccountByUsername(std::string) -> return : void;
            3. getAllAccount() -> return void = printing all of data with serializer 
            4. getAccountBalanceByUsername(std::username) -> return : std::vector(std::string, int balance);
            5. changePassword(std::username, std::string password) -> void
            6. changePin(std::username, std::string password, int PIN[6]) -> void       
            7. ValidateUsername(std::string username) -> Boolean True False
            8. deposit(int amount) -> void 
            9. withdraw(int amount) -> void 
            10. getFullname() -> return : std::string
            11. getUsername() -> return : std::string
            12. getBalance() -> return : integer
        */

        void createAccount(){
            std::string filename = generateFilename(fullName);
            saveData({fullName, userName, passWord, _balance, _PIN}, filename, "database");
        }

        std::vector<std::string> getAccountByFullName(const std::string& full_name){
            if(validatingData(full_name)){
                std::string filename = generateFilename(full_name);
                return getFile(filename, "database");
            }
            return {}; // Empty List
        }

        // Getting all of data by username
        void getAccountByUsername(std::string username){
            if(validateUsername(username)){
            std::cout << "Your Full Name\t: " << fullName << std::endl;
                std::cout << "Your Username\t: " << userName << std::endl;
                std::cout << "Your Balance\t: " << _balance << std::endl; 
            }else{
                std::cout << "Username is not found." << std::endl;
            }
        }

        void getAllAccount(){
            // Because this is only a simulation, we only return 1 account data
            std::cout << "Full Name\t: " << fullName << std::endl;
            std::cout << "Username\t: " << userName << std::endl;
            std::cout << "Balance\t: " << _balance << std::endl;
        }

        int getAccountBalanceByUsername(std::string username){
            if(validateUsername(username)){
                return _balance;
            }
            else{
                return 0;
            }
        }

        void changePassword(std::string username, std::string new_password){
            if(validateUsername(username)){
                if(validatePassword(new_password)){
                    passWord = new_password;
                }
                else{
                    std::cout << "Your new password cannot be the same with the old password." << std::endl;
                }
            }else{
                std::cout << "Username Not Found!" << std::endl;
            }
        }

        void withdraw(int amount){
            if(checkBalance(amount)){
                std::cout << "Your Balance Before\t: " << _balance << std::endl;
                _balance = _balance - amount;
                std::cout << "Your Balance After\t: " << _balance << std::endl;
            }
            else{
                std::cout << "You don't have enough money to withdraw. Please deposit first!" << std::endl;
            }
        }

        void deposit(int amount){
            std::cout << "Amount of Money to Deposit\t: " << amount << std::endl;
            _balance = _balance + amount;
            std::cout << "Your Balance\t: " << _balance << std::endl;
        }

        std::string getFullname(){
            return fullName;
        }

        std::string getUsername(){
            return userName;
        }

        int getBalance(){
            return _balance;
        }
    
};


#endif