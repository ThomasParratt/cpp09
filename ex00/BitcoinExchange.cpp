#include "BitcoinExchange.hpp"

btc::btc(std::string input) : _input(input)
{

}

void    btc::readFile()
{
    std::ifstream   input(_input);
    std::string     date;
    float           value;
    std::string     line;

    if (!input)
    {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

    while (std::getline(input, line))
    {
        size_t  pos = line.find('|');
        if (pos != std::string::npos)
        {
            date = line.substr(0, pos - 1);
        }
        else
        {
            std::cout << "Error: Line contains no |" << std::endl;
            continue ;
        }
        try
        {
            value = std::stof(line.substr(pos + 2));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            continue ;
        }
         _inputMap.insert({date, value});
    }

    for (std::multimap<std::string, float>::iterator it = _inputMap.begin(); it != _inputMap.end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;

}