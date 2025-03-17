#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        _vec.push_back(std::stoul(argv[i]));
    }
}

void    PmergeMe::printVec()
{
    for (auto &it : _vec)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void    PmergeMe::sort(size_t it, size_t pairSize)
{
    std::cout << "it = " << it << std::endl;
    std::cout << "pairSize = " << pairSize << std::endl;
    printVec();
    for (size_t i = it - 1; i + pairSize/2 < _vec.size(); i += pairSize)
    {
        //std::cout << "_vec[i] = " << _vec[i] << "  " << "_vec[i + pairSize/2] = " << _vec[i + pairSize/2] << std::endl;
        //if (_vec[i] > _vec[i + pairSize/2])
        //    std::swap(_vec[i], _vec[i + pairSize/2]);

        std::cout << "_vec[i] = " << _vec[i] << "  " << "_vec[i + pairSize/2] = " << _vec[i + pairSize/2] << std::endl;
        if (_vec[i] > _vec[i + pairSize/2])
            std::swap_ranges(_vec.begin() + i, _vec.begin() + (i + pairSize/2), _vec.begin() + (i + pairSize/2)); //the problem here is that the range size starts at the number we are comparing
    }
    if (pairSize < _vec.size()/3)
    {
        sort(it * 2, pairSize * 2);
    }
}

/*void    PmergeMe::createPairs()
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

void    PmergeMe::extractSmallerElements()
{
    for (auto &it : _seq)
    {
        
    }
}*/