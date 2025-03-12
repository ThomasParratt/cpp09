#pragma once
#include <iostream>
#include <vector>
//#include <variant>

class PmergeMe
{
    private:
        //std::vector<unsigned int>>   _seq;
        std::vector<std::pair<unsigned int, unsigned int>> _seq;
        unsigned int    _odd;
        bool            _isOdd = false;
    public:
        PmergeMe(int argc, char **argv);
        void    printPairs();
        void    sortPairs();
        // 1. make vector
        // 2. make vector with pairs (is step 1. necessary?) ***
        // 3. determine the larger of the two elements in each pair (swap if needed)
        // 4. (recursively) sort the pairs into order based on the size of the first larger element

        // 5. create "main chain" (first larger elements) and "pend" (other elements)
        // 6. insert the "pend" elements into "main chain"
};