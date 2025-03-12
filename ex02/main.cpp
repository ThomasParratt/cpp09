#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "Error: Program has no arguments" << std::endl;
        exit(1);
    }
    PmergeMe sorter = PmergeMe(argc, argv);
    sorter.printPairs();
    sorter.sortPairs();
    sorter.printPairs();
}