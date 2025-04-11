#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./btc <filename>" << std::endl;
        exit(1);
    }
    btc bitcoin;
    
    bitcoin.readData();
    bitcoin.printResults(argv[1]);
}

// date | value
// 2011-01-03 | 3
// 2011-01-03 | 2
// 2011-01-03 | 1
// 2011-01-03 | 1.2
// 2011-01-09 | 1
// 2012-01-11 | -1
// 2001-42-42
// 2012-01-11 | 1
// 2012-01-11 | 2147483648
// 2024-02-29 | 1
// 2023-02-29 | 1
// 2023-04-31 | 1
// 1900-04-10 | 1
// 2022-03-29 | 1
// 2022-03-30 | 1
// 2025-04-11 | 1
// 3000-03-30 | 1