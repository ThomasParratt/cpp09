#pragma once
#include <iostream>
#include <vector>
//#include <variant>
#include <ranges>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _vec;
        std::vector<unsigned int>   _jacobSeq;
        //std::vector<std::pair<unsigned int, unsigned int>> _seq;
        //unsigned int    _odd;
        //bool            _isOdd = false;
    public:
        PmergeMe(int argc, char **argv);
        void    printVec(std::string str, std::vector<unsigned int>& vec);
        //void    sort(size_t groupSize);
        void    binaryInsert(std::vector<unsigned int>& sorted, int value);
        void    mergeInsertSort();
        //void    createPairs();
        //void    printPairs();
        //void    sortPairs();
        //void    extractSmallerElements();
};