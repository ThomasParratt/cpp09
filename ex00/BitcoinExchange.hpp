#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <ctime>

class btc
{
    private:
        std::string _input;
        std::string _data;
        std::map<std::string, float>  _dataMap;
    public:
        btc(std::string input, std::string data);
        void    readData();
        void    readInput();
        bool    isValidDate(std::string date);
        float   getResult(std::string date, float value);
};