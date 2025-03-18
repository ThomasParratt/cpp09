#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        _vec.push_back(std::stoul(argv[i]));
    }

    _jacobSeq.push_back(0);
    _jacobSeq.push_back(1);
    int i = 2;
    while (_jacobSeq.back() < _vec.size()) 
    {
        _jacobSeq.push_back(_jacobSeq[i-1] + 2 * _jacobSeq[i-2]);
        i++;
    }
}

void    PmergeMe::printVec(std::string str, std::vector<unsigned int>& vec)
{
    std::cout << str;
    for (auto &it : vec)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

// void PmergeMe::sort(size_t groupSize) 
// {
//     if (groupSize > _vec.size()) return;  // Base case: when group size exceeds vector size

//     std::cout << "groupSize = " << groupSize << std::endl;
//     printVec();

//     for (size_t i = 0; i + groupSize < _vec.size(); i += 2 * groupSize) 
//     {
//         size_t leftStart = i;
//         size_t rightStart = i + groupSize;

//         // Find comparison points (e.g., last of left group, last of right group)
//         int leftCompare = _vec[leftStart + groupSize - 1];
//         int rightCompare = _vec[rightStart + groupSize - 1];

//         // If the left group "should" be after the right group, swap them
//         if (leftCompare > rightCompare && (leftStart + groupSize - 1 < _vec.size()) && (rightStart + groupSize - 1 < _vec.size())) 
//         {
//             std::cout << "Swapping groups starting at " << leftStart << " and " << rightStart << std::endl;
//             std::swap_ranges(_vec.begin() + leftStart, _vec.begin() + leftStart + groupSize, _vec.begin() + rightStart);
//         }
//     }
//     sort(groupSize * 2);
// }

// Binary search insert helper
void PmergeMe::binaryInsert(std::vector<unsigned int>& sorted, int value) 
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

// Full merge-insert sort driver
void PmergeMe::mergeInsertSort() 
{
    std::vector<unsigned int> mainChain; //larger
    std::vector<unsigned int> pending; //smaller

    //Step 1: Pairing
    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        int first = _vec[i];
        int second = _vec[i + 1];
        if (first > second) 
        {
            mainChain.push_back(first);
            pending.push_back(second);
        } 
        else 
        {
            mainChain.push_back(second);
            pending.push_back(first);
        }
    }
    // Handle leftover
    if (_vec.size() % 2 != 0) mainChain.push_back(_vec.back());
    // Replace internal _vec with main chain for recursive sort
    _vec = mainChain;
    if (_vec.size() > 1) 
    {
        mergeInsertSort(); // Recursively sort the vector
    }
    printVec("mainChain = ", mainChain);
    printVec("pending = ", pending);
    // // Step 2: Insert pending elements using binary insert 
    // for (int val : pending) 
    // {
    //     binaryInsert(_vec, val);
    //     std::cout << "After inserting " << val << ": ";
    //     printVec("", _vec);
    // }

    // Step 2: Insert pending elements using binary insert, but use Jacobsthal numbers
    std::vector<bool> tracker(pending.size(), false); // Track which elements have been inserted
    size_t jacobIdx = 0;

    for (size_t i = 0; i < pending.size(); i++) 
    {
        // Use Jacobsthal sequence to determine whether to insert this pending value
        if (jacobIdx < _jacobSeq.size() && _jacobSeq[jacobIdx] == i) 
        {
            // If the current index matches a Jacobsthal number, perform the binary insert
            binaryInsert(_vec, pending[i]);
            std::cout << "After inserting " << pending[i] << " (Jacobsthal " << _jacobSeq[jacobIdx] << "): ";
            printVec("", _vec);
            jacobIdx++; // Move to the next Jacobsthal number
        }
    }
    
    // Insert remaining elements if not yet inserted using Jacobsthal
    for (size_t i = jacobIdx; i < pending.size(); i++) 
    {
        binaryInsert(_vec, pending[i]);
        std::cout << "After inserting " << pending[i] << ": ";
        printVec("", _vec);
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