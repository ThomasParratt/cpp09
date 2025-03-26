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