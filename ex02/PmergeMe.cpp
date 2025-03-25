#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& obj) : _jacob(obj._jacob), _vec(obj._vec), _deq(obj._deq)
{

}

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
    if (_vec.size() <= 1)
    {
        std::cerr << "Error: Cannot sort one number" << std::endl;
        exit(1);
    }
    generateJacobsthal();
}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
    if (this != &obj)
    {
        _jacob = obj._jacob;
        _vec = obj._vec;
        _deq = obj._deq;
    }
    return (*this);
}
        
PmergeMe::~PmergeMe()
{

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
}

void PmergeMe::printVec(const std::string& label, const std::vector<int>& vec) 
{
    std::cout << label;
    for (auto val : vec) 
        std::cout << val << " ";
    std::cout << std::endl;
}

void PmergeMe::printDeq(const std::string& label, const std::deque<int>& deq) 
{
    std::cout << label;
    for (auto val : deq) 
        std::cout << val << " ";
    std::cout << std::endl;
}

void PmergeMe::binaryInsertVec(std::vector<int>& sorted, int value) 
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

void PmergeMe::binaryInsertDeq(std::deque<int>& sorted, int value)
{
    auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, value);
}

void PmergeMe::mergeInsertSortVector() 
{
    if (_vec.size() <= 1) 
        return ;

    // Step 1: Pairing and creating larger and smaller vectors
    std::vector<int> larger;
    std::vector<int> smaller;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        int first = _vec[i];
        int second = _vec[i + 1];
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

    // If odd, last element goes to larger
    if (_vec.size() % 2 != 0) 
        larger.push_back(_vec.back());

    // printVec("Larger = ", larger);
    // printVec("Smaller = ", smaller);
    // std::cout << std::endl;

    // Recursive sort
    _vec = larger;
    mergeInsertSortVector();

    //printVec("Sorted larger = ", _vec);
    //printVec("Pending smaller elements = ", smaller);

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::vector<bool> inserted(smaller.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= smaller.size()) 
            break ;
        if (inserted[idx])
            continue ;
        binaryInsertVec(_vec, smaller[idx]);
        inserted[idx] = true;
        //std::cout << "After inserting (Jacobsthal " << _jacob[j] << ") " << smaller[idx] << ": ";
        //printVec("", _vec);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < smaller.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsertVec(_vec, smaller[i]);
            //std::cout << "After inserting remaining " << smaller[i] << ": ";
            //printVec("", _vec);
        }
    }
    //std::cout << std::endl;
}


void PmergeMe::mergeInsertSortDeque() 
{
    if (_deq.size() <= 1) 
        return ;

    std::deque<int> larger;
    std::deque<int> smaller;

    for (size_t i = 0; i + 1 < _deq.size(); i += 2) 
    {
        int first = _deq[i];
        int second = _deq[i + 1];
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

    if (_deq.size() % 2 != 0) 
        larger.push_back(_deq.back());

    _deq = larger;
    mergeInsertSortDeque();

    std::deque<bool> inserted(smaller.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= smaller.size()) 
            break ;
        if (inserted[idx])
            continue;
        binaryInsertDeq(_deq, smaller[idx]);
        inserted[idx] = true;
    }

    for (size_t i = 0; i < smaller.size(); i++) 
    {
        if (!inserted[i]) 
            binaryInsertDeq(_deq, smaller[i]);
    }
}

std::vector<int>   PmergeMe::getVec()
{
    return (_vec);
}

std::deque<int>   PmergeMe::getDeq()
{
    return (_deq);
}

