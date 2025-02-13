#include "PmergeMe.hpp"

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        std::cout << "Error: Program has no arguments" << std::endl;
        exit(1);
    }

    std::vector<unsigned int>   sequence;

    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
        try
        {
            sequence.push_back(std::stoi(argv[i]));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    PmergeMe toSort = PmergeMe(sequence);
}