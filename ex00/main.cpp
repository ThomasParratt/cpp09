#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./btc <filename>" << std::endl;
        exit(1);
    }
    btc bitcoin = btc(argv[1], "data.csv");
    bitcoin.readData(); // add file into here as an argument and then use defaut contructor instead
    bitcoin.printResults();

    // std::cout << "Valid: " << bitcoin.isValidDate("2024-02-29") << std::endl; // Leap year case
    // std::cout << "Valid: " << bitcoin.isValidDate("2023-02-29") << std::endl; // Invalid non-leap year
    // std::cout << "Valid: " << bitcoin.isValidDate("2023-04-31") << std::endl; // Invalid day for April
    // std::cout << "Valid: " << bitcoin.isValidDate("2023-12-25") << std::endl; // Valid date
}