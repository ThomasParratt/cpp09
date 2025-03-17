#pragma once
#include <iostream>
#include <vector>
//#include <variant>
#include <ranges>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _vec;
        //std::vector<std::pair<unsigned int, unsigned int>> _seq;
        //unsigned int    _odd;
        //bool            _isOdd = false;
    public:
        PmergeMe(int argc, char **argv);
        void    printVec();
        void    sort(size_t it, size_t pairSize);
        //void    createPairs();
        //void    printPairs();
        //void    sortPairs();
        //void    extractSmallerElements();
};