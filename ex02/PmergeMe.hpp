#pragma once
#include <iostream>
#include <vector>
//#include <ranges>
#include <chrono>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _vec;
        std::vector<unsigned int>   _jacob;
    public:
        PmergeMe(int argc, char **argv);
        void    generateJacobsthal();
        void    printVec(const std::string& label, const std::vector<unsigned int>& vec);
        void    binaryInsert(std::vector<unsigned int>& sorted, unsigned int value);
        void    mergeInsertSort();
        std::vector<unsigned int>   getVec();
};