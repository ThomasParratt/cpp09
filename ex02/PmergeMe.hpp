#pragma once
#include <iostream>
#include <vector>
//#include <variant>

class PmergeMe
{
    private:
        std::vector<unsigned int>   _input;
        std::vector<std::pair<unsigned int, unsigned int>> _seq;
        unsigned int    _odd;
        bool            _isOdd = false;
    public:
        PmergeMe(int argc, char **argv);
        void    createPairs();
        void    printPairs();
        void    sortPairs();
};


// 1. Pairing Elements

// Group the numbers into pairs.
// Compare each pair and sort them (smaller number first, larger second).

// 2. Creating a Partially Sorted List

// Take the smallest element from each sorted pair and sort them recursively using the same method. This step creates an "insertion order" list.

// 3. Merging and Inserting the Larger Elements

// The larger numbers from the original pairs are inserted into the sorted sequence one by one, using a carefully chosen insertion order to minimize comparisons.

// 4. Final Sorting Pass

// Continue merging and inserting until the whole sequence is sorted.