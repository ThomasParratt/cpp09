#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./btc <input file>" << std::endl;
        exit(1);
    }
    btc bitcoin = btc(argv[1]);
    bitcoin.readFile();
}