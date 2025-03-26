#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>

class PmergeMe
{
    private:
        std::vector<size_t> _jacob;
        std::vector<int>    _vec;
        std::deque<int>     _deq;
    public:
        PmergeMe() = delete;
        PmergeMe(const PmergeMe& obj);
        PmergeMe(int argc, char **argv);
        PmergeMe& operator=(const PmergeMe& obj);
        ~PmergeMe();
        void    generateJacobsthal();
        void    printVec(const std::string& label, const std::vector<int>& vec);
        void    printDeq(const std::string& label, const std::deque<int>& deq); 
        void    binaryInsertVec(std::vector<int>& sorted, int value);
        void    binaryInsertDeq(std::deque<int>& sorted, int value);
        void    mergeInsertSortVector();
        void    mergeInsertSortDeque();
        std::vector<int>    getVec() const;
        std::deque<int>     getDeq() const;
};