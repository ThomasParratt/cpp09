#include "BitcoinExchange.hpp"

btc::btc(std::string input) : _input(input)
{

}

void    btc::readFile()
{
    std::ifstream   input(_input);
    std::string     date;
    float           value;

    if (!input)
    {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }
        
    // while (input >> date >> value)
    // {
    //     _inputMap[date] = value;
    // }

    while (std::getline(input, date, '|') && (input >> value)) 
    {
        _inputMap[date] = value;
    }

    if (_inputMap.empty())
        std::cout << "No data was read from file" << std::endl;
    
    for (auto &pair : _inputMap) 
    {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
}