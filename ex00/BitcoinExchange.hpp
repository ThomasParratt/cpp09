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
        std::multimap<std::string, float>  _inputMap;
        std::multimap<std::string, float>  _dataMap;
    public:
        btc(std::string input, std::string data);
        void    readInput();
        void    readData();
        bool    isValidDate(const std::string& date);
};