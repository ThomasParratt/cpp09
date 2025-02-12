#pragma once
#include <iostream>
#include <fstream>
#include <map>

class btc
{
    private:
        std::string _input;
        std::multimap<std::string, float>  _inputMap;
    public:
        btc(std::string input);
        void    readFile();
};