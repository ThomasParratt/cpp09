#pragma once
#include <iostream>
#include <fstream>
#include <map>

class btc
{
    private:
        std::string _input;
        std::map<std::string, int>  _inputMap;
    public:
        btc(std::string input);
        void    readFile();
};