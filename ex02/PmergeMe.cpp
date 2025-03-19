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
            _deq.push_back(num);
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

void PmergeMe::printDeq(const std::string& label, const std::deque<unsigned int>& deq) 
{
    std::cout << label;
    for (auto val : deq) 
        std::cout << val << " ";
    std::cout << std::endl;
}

void PmergeMe::binaryInsertVec(std::vector<unsigned int>& sorted, unsigned int value) 
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

void PmergeMe::binaryInsertDeq(std::deque<unsigned int>& sorted, unsigned int value)
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

void PmergeMe::mergeInsertSortVector() 
{
    if (_vec.size() <= 1) 
        return ;

    // Step 1: Pairing and creating mainChain and pending vectors
    std::vector<unsigned int> larger;
    std::vector<unsigned int> smaller;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        unsigned int first = _vec[i];
        unsigned int second = _vec[i + 1];
        if (first > second) 
        {
            larger.push_back(first);
            smaller.push_back(second);
        } 
        else 
        {
            larger.push_back(second);
            smaller.push_back(first);
        }
    }

    // If odd, last element goes to mainChain
    if (_vec.size() % 2 != 0) 
        larger.push_back(_vec.back());

    // Recursive sort on mainChain
    _vec = larger;
    mergeInsertSortVector();  // Sort the main chain first

    //printVec("Sorted mainChain = ", _vec);
    //printVec("Pending elements = ", pending);

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::vector<bool> inserted(smaller.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= smaller.size()) 
            break ;
        if (inserted[idx]) // Skip the double 1
            continue;
        binaryInsertVec(_vec, smaller[idx]);
        inserted[idx] = true;
        //std::cout << "After inserting (Jacobsthal " << _jacob[j] << ") " << pending[idx] << ": ";
        //printVec("", _vec);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < smaller.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsertVec(_vec, smaller[i]);
            //std::cout << "After inserting remaining " << pending[i] << ": ";
            //printVec("", _vec);
        }
    }
    //std::cout << std::endl;
}

void PmergeMe::mergeInsertSortDeque() 
{
    if (_deq.size() <= 1) 
        return ;

    // Step 1: Pairing and creating mainChain and pending vectors
    std::deque<unsigned int> larger;
    std::deque<unsigned int> smaller;

    for (size_t i = 0; i + 1 < _deq.size(); i += 2) 
    {
        unsigned int first = _deq[i];
        unsigned int second = _deq[i + 1];
        if (first > second) 
        {
            larger.push_back(first);
            smaller.push_back(second);
        } 
        else 
        {
            larger.push_back(second);
            smaller.push_back(first);
        }
    }

    // If odd, last element goes to mainChain
    if (_deq.size() % 2 != 0) 
        larger.push_back(_deq.back());

    // Recursive sort on mainChain
    _deq = larger;
    mergeInsertSortDeque();  // Sort the main chain first

    //printVec("Sorted mainChain = ", _vec);
    //printVec("Pending elements = ", pending);

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::deque<bool> inserted(smaller.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= smaller.size()) 
            break ;
        if (inserted[idx]) // Skip the double 1
            continue;
        binaryInsertDeq(_deq, smaller[idx]);
        inserted[idx] = true;
        //std::cout << "After inserting (Jacobsthal " << _jacob[j] << ") " << pending[idx] << ": ";
        //printVec("", _vec);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < smaller.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsertDeq(_deq, smaller[i]);
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

std::deque<unsigned int>   PmergeMe::getDeq()
{
    return (_deq);
}

