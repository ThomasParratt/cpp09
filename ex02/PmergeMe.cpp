#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    for (int i = 1; i < argc; i+=2)
    {
        _seq.push_back({std::stoul(argv[i]), std::stoul(argv[i + 1])});
        //std::cout << argv[i] << " ";
    }
    //std::cout << std::endl;
}