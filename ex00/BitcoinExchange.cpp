#include "BitcoinExchange.hpp"

btc::btc(std::string input) : _input(input)
{

}

void    btc::readFile()
{
    std::ifstream   input(_input);
    std::string     str;

    if (input.is_open())
    {
        while (input)
        {
            input >> str;
            std::cout << str << std::endl;
        }
    }
}