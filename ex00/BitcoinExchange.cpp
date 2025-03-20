#include "BitcoinExchange.hpp"

btc::btc(std::string input, std::string data) : _input(input), _data(data)
{

}

void    btc::readData()
{
    std::ifstream   input(_data);
    std::string     date;
    float           value;
    std::string     line;

    if (!input)
    {
        std::cerr << "Error: Could not open file" << std::endl;
        exit(1);
    }

    while (std::getline(input, line))
    {
        size_t  pos = line.find(',');
        date = line.substr(0, pos);
        if (date == "date")
            continue ;
        if (line.substr(pos + 1) == "0")
            value = 0;
        else
            value = std::stof(line.substr(pos + 1));
         _dataMap.insert({date, value});
    }

    // std::cout << std::endl << "data multimap contents: " << std::endl;
    // for (std::map<std::string, float>::iterator it = _dataMap.begin(); it != _dataMap.end(); ++it)
    //     std::cout << it->first << " -> " << it->second << std::endl;
}

void    btc::printResults()
{
    std::ifstream   input(_input);
    std::string     date;
    float           value;
    std::string     line;

    if (!input)
    {
        std::cerr << "Error: Could not open file" << std::endl;
        exit(1);
    }

    while (std::getline(input, line))
    {
        std::regex syntax(R"(^[^]+ \| [^]+$)");
        if (!std::regex_match(line, syntax))
        {
            std::cout << "Error: Wrong line format" << std::endl;
            continue ;
        }

        size_t  pos = line.find('|');
        date = line.substr(0, pos - 1);
        if (date == "date")
            continue ;
        if (!isValidDate(date))
            continue ;

        try
        {
            value = std::stof(line.substr(pos + 2));
            if (value < 0 || value > 1000)
            {
                std::cout << "Error: Invalid value => " << value << std::endl;
                continue ;
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Error: Invalid value => " << line.substr(pos + 2) << std::endl;
            continue ;
        }
        std::cout << date << " => " << value << " = " << getResult(date, value) << std::endl;
    }
}

bool btc::isValidDate(std::string date)
{
    std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, datePattern))
    {
        std::cout << "Error: Invalid date format => " << date << std::endl;
        return false;
    }

    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
    if (month < 1 || month > 12)
    {
        std::cout << "Error: Invalid month in date => " << date << std::endl;
        return false;
    }

    std::tm timeStruct = {};
    timeStruct.tm_year = year - 1900; // Years since 1900
    timeStruct.tm_mon = month - 1;    // Zero-based month (0 = Jan, 11 = Dec)
    timeStruct.tm_mday = day;

    if (std::mktime(&timeStruct) == -1 || timeStruct.tm_mday != day)
    {
        std::cout << "Error: Invalid day in date => " << date << std::endl;
        return false;
    }

    return true;
}

float   btc::getResult(std::string date, float value)
{
    for (std::map<std::string, float>::iterator it = _dataMap.begin(); it != _dataMap.end(); ++it)
    {
        if (it->first > date)
        {
            it--;
            return (value * it->second);
        }
    }
    return (0);
}