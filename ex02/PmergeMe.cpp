#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv) 
{
    try 
    {
        for (int i = 1; i < argc; i++)
        {
            int num = std::stoi(argv[i]);
            if (num < 0)
            {
                std::cerr << "Error: Input cannot be negative" << std::endl;
                exit(1);
            }
            _vec.push_back(num);
        }
    } 
    catch (std::exception& e) 
    {
        std::cerr << "Invalid input: " << e.what() << std::endl;
        exit(1);
    }
    //printVec("Initial vector = ", _vec);
    //std::cout << "vector size = " << _vec.size() << std::endl;
    generateJacobsthal();
}

void PmergeMe::generateJacobsthal() 
{
    _jacob.push_back(0);
    _jacob.push_back(1);
    unsigned int i = 2;
    while (_jacob.back() < _vec.size()) 
    {
        _jacob.push_back(_jacob[i - 1] + 2 * _jacob[i - 2]);
        i++;
    }
    //printVec("Jacobsthal sequence = ", _jacob);
    //std::cout << std::endl;
}

void PmergeMe::printVec(const std::string& label, const std::vector<unsigned int>& vec) 
{
    std::cout << label;
    for (auto val : vec) 
        std::cout << val << " ";
    std::cout << std::endl;
}

void PmergeMe::binaryInsert(std::vector<unsigned int>& sorted, unsigned int value) 
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

void PmergeMe::mergeInsertSort() 
{
    if (_vec.size() <= 1) 
        return ;

    // Step 1: Pairing and creating mainChain and pending vectors
    std::vector<unsigned int> mainChain;
    std::vector<unsigned int> pending;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        unsigned int first = _vec[i];
        unsigned int second = _vec[i + 1];
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

    // If odd, last element goes to mainChain
    if (_vec.size() % 2 != 0) 
        mainChain.push_back(_vec.back());

    // Recursive sort on mainChain
    _vec = mainChain;
    mergeInsertSort();  // Sort the main chain first

    //printVec("Sorted mainChain = ", _vec);
    //printVec("Pending elements = ", pending);

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::vector<bool> inserted(pending.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= pending.size()) 
            break ;
        if (inserted[idx]) // Skip the double 1
            continue;
        binaryInsert(_vec, pending[idx]);
        inserted[idx] = true;
        //std::cout << "After inserting (Jacobsthal " << _jacob[j] << ") " << pending[idx] << ": ";
        //printVec("", _vec);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < pending.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsert(_vec, pending[i]);
            //std::cout << "After inserting remaining " << pending[i] << ": ";
            //printVec("", _vec);
        }
    }
    //std::cout << std::endl;
}

std::vector<unsigned int>   PmergeMe::getVec()
{
    return (_vec);
}

