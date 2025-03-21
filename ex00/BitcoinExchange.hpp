#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <ctime>

class btc
{
    private:
        std::string _data;
        std::map<std::string, float>  _dataMap;
    public:
        btc();
        //btc(const btc& obj);
        //btc& operator=(const btc& obj);
        void    readData();
        void    printResults(std::string inputFile);
        bool    isValidDate(std::string date);
        float   getResult(std::string date, float value);
};