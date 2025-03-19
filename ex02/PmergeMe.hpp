#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _jacob;
        std::vector<unsigned int>   _vec;
        std::deque<unsigned int>    _deq;
    public:
        PmergeMe(int argc, char **argv);
        void    generateJacobsthal();
        void    printVec(const std::string& label, const std::vector<unsigned int>& vec);
        void    printDeq(const std::string& label, const std::deque<unsigned int>& deq); 
        void    binaryInsertVec(std::vector<unsigned int>& sorted, unsigned int value);
        void    binaryInsertDeq(std::deque<unsigned int>& sorted, unsigned int value);
        void    mergeInsertSortVector();
        void    mergeInsertSortDeque();
        std::vector<unsigned int>   getVec();
        std::deque<unsigned int>   getDeq();
};