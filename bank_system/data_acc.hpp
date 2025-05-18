#ifndef DATA_ACC_H
#define DATA_ACC_H

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

struct AccountData
{
    /* data */
    std::string fullName;
    std::string userName;
    std::string passWord;
    int _balance;
    std::vector<int> _PIN;
};

inline bool exist_filedir(const fs::path& p){
    return fs::exists(p);
}

inline bool create_directories(const std::string& dirname ){
    const fs::path dir(dirname);
    if(!exist_filedir(dir)){
        return fs::create_directory(dir);
    }else{
        return false;
    }
}

void writeData(const AccountData& acc, const std::string& path_file){
    std::ofstream file(path_file, std::ios::app);
    if(file.is_open()){
            file << acc.fullName << '\n'
                 << acc.userName << '\n'
                 << acc.passWord << '\n'
                 << acc._balance << '\n';
            for(int digit : acc._PIN) file << digit;
            file << "\n";
            file.close();
    }
}

inline std::vector<std::string> getFile(const std::string& filename, const std::string& path){
    const fs::path directory(path);
    std::vector<std::string> lines;
    if(exist_filedir(directory)){
        std::string filepath = directory / filename;
        std::ifstream file(filepath);
        std::string line;

        // Check if file opened success
        if(file.is_open()){
            while(std::getline(file, line)){
                lines.push_back(line);
            }
        }
    }

    return lines;
}

void saveData(const AccountData& acc, const std::string& filename, const std::string& path){
    fs::path directory(path);
    if(!exist_filedir(directory)){
        create_directories(path);
    }
    fs::path filepath = directory / filename;
    writeData(acc, filepath.string());
    std::cout << "File saved in" << filepath << std::endl;
}


#endif