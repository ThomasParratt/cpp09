#include "BitcoinExchange.hpp"

btc::btc() : _data("data.csv"){}

btc::btc(const btc& obj) : _data(obj._data), _dataMap(obj._dataMap){}

btc& btc::operator=(const btc& obj)
{
    if (this != &obj)
    {
        _data = obj._data;
        _dataMap = obj._dataMap;
    }
    return (*this);
}

btc::~btc(){}

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
        value = std::stof(line.substr(pos + 1));
         _dataMap.insert({date, value});
    }

    // std::cout << std::endl << "data multimap contents: " << std::endl;
    // for (std::map<std::string, float>::iterator it = _dataMap.begin(); it != _dataMap.end(); ++it)
    //     std::cout << it->first << " -> " << it->second << std::endl;
}

void    btc::printResults(std::string inputFile)
{
    std::ifstream   input(inputFile);
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
        std::regex syntax(R"(^.+ \| .+$)");
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

    // comparing tm_mday ensures invalid days are caught // std::mktime(&timeStruct) converts the std::tm into a timestamp (seconds since 1970)
    if (std::mktime(&timeStruct) == -1 || timeStruct.tm_mday != day) // if the date was invalid, mktime would have changed it
    {
        std::cout << "Error: Invalid day in date => " << date << std::endl;
        return false;
    }

    auto it = _dataMap.lower_bound(date);
    if (it == _dataMap.begin() && date < it->first)
    {
        std::cout << "Error: Date before database records => " << date << std::endl;
        return false;
    }

    return true;
}

float btc::getResult(std::string date, float value)
{
    auto it = _dataMap.lower_bound(date);
    if (it != _dataMap.begin() && (it == _dataMap.end() || it->first != date))
        --it;
    return (value * it->second);
}
