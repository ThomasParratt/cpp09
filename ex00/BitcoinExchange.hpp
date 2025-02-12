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
        std::multimap<std::string, float>  _inputMap;
    public:
        btc(std::string input);
        void    readFile();
        bool    isValidDate(const std::string& date);
};