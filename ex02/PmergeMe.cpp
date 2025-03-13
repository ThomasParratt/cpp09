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

void    PmergeMe::createPairs()
{
    std::cout << "Creating pairs.." << std::endl;
    std::vector<std::pair<unsigned int, unsigned int>> _seq2;
    unsigned int    _odd2;
    bool            _isOdd2 = false;

    std::cout << "Size of _seq = " << sizeof(_seq) << std::endl;
    for (size_t i = 0; i < sizeof(_seq) / 5; i+=2) //Probelsm with size. Seems to work when divide by 5...
    {
        if (i + 1 < sizeof(_seq))
            _seq2.push_back(std::make_pair(_seq[i].first, _seq[i + 1].first));
        else
        {
            _isOdd2 = true;
            _odd2 = _seq[i].first;
        }
    }
    //Print _seq2 pairs
    for (auto &it : _seq2)
        std::cout << "First: " << it.first << ", Second: " << it.second << std::endl;
    if (_isOdd2)
        std::cout << "First: " << _odd2 << std::endl;
    //Sort _seq2 pairs
    for (auto &it : _seq2)
    {
        if (it.first > it.second)
        {
            std::swap(it.first, it.second);
        }
    }
    //Print _seq2 pairs
    for (auto &it : _seq2)
        std::cout << "First: " << it.first << ", Second: " << it.second << std::endl;
    if (_isOdd2)
        std::cout << "First: " << _odd2 << std::endl;
}

void    PmergeMe::printPairs()
{
    std::cout << "Printing pairs..." << std::endl;
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

void    extractSmallerElements()
{
    
}