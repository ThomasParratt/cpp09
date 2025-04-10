#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <chrono>

class PmergeMe
{
    private:
        std::vector<int>    _vec;
        std::deque<int>     _deq;
    public:
        PmergeMe() = delete;
        PmergeMe(const PmergeMe&);
        PmergeMe(int, char**);
        PmergeMe& operator=(const PmergeMe&);
        ~PmergeMe();
       
        void    printVec(const std::string&, const std::vector<int>&);
        void    printDeq(const std::string&, const std::deque<int>&);
        void    printVecPairs(const std::vector<std::pair<int,int>>&);
        void    printDeqPairs(const std::deque<std::pair<int,int>>&);

        std::vector<size_t>	generateJacobsthal(size_t);
        
        void    insertionVec(std::vector<int>&, std::vector<std::pair<int, int>>&);
        void    insertionDeq(std::deque<int>&, std::deque<std::pair<int, int>>&);
        size_t  findVecPartner(size_t, std::vector<std::pair<int, int>>&);
        size_t	findDeqPartner(size_t, std::deque<std::pair<int, int>>&);

        void    mergeInsertSortVector();
        void    mergeInsertSortDeque();

        std::vector<int>    getVec() const;
        std::deque<int>     getDeq() const;
};