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

void PmergeMe::printVecPairs(const std::vector<std::pair<int,int>>& pairs)
{
    std::cout << "Pairs: ";
    for (auto pair : pairs)
        std::cout << "{" << pair.first << "," << pair.second << "} ";
    std::cout << std::endl;
}

void PmergeMe::printDeqPairs(const std::deque<std::pair<int,int>>& pairs)
{
    std::cout << "Pairs: ";
    for (auto pair : pairs)
        std::cout << "{" << pair.first << "," << pair.second << "} ";
    std::cout << std::endl;
}

void PmergeMe::binaryInsertVec(std::vector<int>& sorted, int value, size_t idx) 
{
    auto pos = std::lower_bound(sorted.begin(), sorted.begin() + idx + 1, value);
    sorted.insert(pos, value);
}

void PmergeMe::binaryInsertDeq(std::deque<int>& sorted, int value, size_t idx)
{
    auto pos = std::lower_bound(sorted.begin(), sorted.begin() + idx + 1, value);
    sorted.insert(pos, value);
}

void PmergeMe::mergeInsertSortVector()
{
    if (_vec.size() <= 1) 
        return ;
    
    //printVec("Vector = ", _vec);

    bool    odd = false;
    int     oddValue;     

    // Step 1: Creating pairs
    std::vector<std::pair<int,int>> pairs;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2)
    {
        int first = _vec[i];
        int second = _vec[i + 1];
        if (first > second) 
            pairs.emplace_back(second, first);
        else 
            pairs.emplace_back(first, second);
    }

    // If odd, last element goes to oddValue
    if (_vec.size() % 2 != 0)
    {
        oddValue = _vec.back();
        //std::cout << "Odd value = " << oddValue << std::endl;
        odd = true;
    }

    //printVecPairs(pairs);
    //std::cout << std::endl;

    std::vector<int> larger;

    for (auto pair : pairs)
        larger.push_back(pair.second);

    // Recursive sort
    _vec = larger;
    mergeInsertSortVector();

    //printVec("Sorted larger = ", _vec);
    //printVecPairs(pairs);

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::vector<bool> inserted(pairs.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= pairs.size())
            break ;
        if (inserted[idx])
            continue ;
        binaryInsertVec(_vec, pairs[idx].first, idx);
        inserted[idx] = true;
        //std::cout << "After inserting smaller (Jacobsthal " << _jacob[j] << ") " << pairs[idx].first << ": ";
        //printVec("", _vec);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < pairs.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsertVec(_vec, pairs[i].first, i);
            //std::cout << "After inserting smaller remaining " << pairs[i].first << ": ";
            //printVec("", _vec);
        }
    }
    if (odd)
    {
        binaryInsertVec(_vec, oddValue, _vec.size());
        //std::cout << "After inserting odd value " << oddValue << ": ";
    }
    //std::cout << std::endl;
}

void PmergeMe::mergeInsertSortDeque()
{
    if (_deq.size() <= 1) 
        return ;

    bool    odd = false;
    int     oddValue;     

    // Step 1: Creating pairs
    std::deque<std::pair<int,int>> pairs;

    for (size_t i = 0; i + 1 < _deq.size(); i += 2)
    {
        int first = _deq[i];
        int second = _deq[i + 1];
        if (first > second) 
            pairs.emplace_back(second, first);
        else 
            pairs.emplace_back(first, second);
    }

    // If odd, last element goes to oddValue
    if (_deq.size() % 2 != 0)
    {
        oddValue = _deq.back();
        odd = true;
    }

    std::deque<int> larger;

    for (auto pair : pairs)
        larger.push_back(pair.second);

    // Recursive sort
    _deq = larger;
    mergeInsertSortDeque();

    // Step 2: Insert pending elements using Jacobsthal sequence
    std::deque<bool> inserted(pairs.size(), false);

    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= pairs.size())
            break ;
        if (inserted[idx])
            continue ;
        binaryInsertDeq(_deq, pairs[idx].first, idx);
        inserted[idx] = true;
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < pairs.size(); i++) 
    {
        if (!inserted[i]) 
            binaryInsertDeq(_deq, pairs[i].first, i);
    }
    if (odd)
        binaryInsertDeq(_deq, oddValue, _deq.size());
}

std::vector<int>   PmergeMe::getVec() const
{
    return (_vec);
}

std::deque<int>   PmergeMe::getDeq() const
{
    return (_deq);
}

