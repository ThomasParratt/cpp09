#pragma once
#include <iostream>
#include <fstream>

class btc
{
    private:
        std::string _input;
    public:
        btc(std::string input);
        void    readFile();
};