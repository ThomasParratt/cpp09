#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "Error: Program has no arguments" << std::endl;
        exit(1);
    }
    for (int i = 0; i < argc; i++)
        std::cout << argv[i] << std::endl;
}