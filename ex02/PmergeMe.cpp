#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    for (int i = 1; i < argc; i+=2)
    {
        if (i + 1 < argc)
            _seq.push_back(std::make_pair(std::stoul(argv[i]), std::stoul(argv[i + 1])));
        else
        {
            _isOdd = true;
            _odd = std::stoul(argv[i]);
        }
    }
}

void    PmergeMe::printPairs()
{
    for (auto &it : _seq)
        std::cout << "First: " << it.first << ", Second: " << it.second << std::endl;
    if (_isOdd)
        std::cout << "First: " << _odd << std::endl;
}

void    PmergeMe::sortPairs()
{
    std::cout << "Sorting pairs..." << std::endl; 
    for (auto &it : _seq)
    {
        if (it.first > it.second)
        {
            std::swap(it.first, it.second);
        }
    }
}