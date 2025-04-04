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
    _jacob.push_back(1);
    _jacob.push_back(2);

    // Generate the sequence until it covers the necessary size
    while (_jacob.back() <= _vec.size()) {
        size_t nextValue = 2 * _jacob.back() + _jacob[_jacob.size() - 2];
        _jacob.push_back(nextValue);
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

void PmergeMe::binaryInsertVec(std::vector<int>& arr, int value) 
{
    auto pos = std::lower_bound(arr.begin(), arr.end(), value);
    arr.insert(pos, value);
}

void PmergeMe::binaryInsertDeq(std::deque<int>& sorted, int value, size_t idx)
{
    auto pos = std::lower_bound(sorted.begin(), sorted.begin() + idx + 1, value);
    sorted.insert(pos, value);
}

void PmergeMe::mergeSortedBlocks(std::vector<int>& arr) 
{
    size_t n = arr.size();
    std::vector<int> temp(arr.size());
    for (size_t blockSize = 2; blockSize / 2 < n; blockSize *= 2) 
    {
        std::cout << "Block size = " << blockSize << std::endl;
        printVec("arr = ", arr);
        for (size_t i = 0; i < n; i += blockSize) 
        {
            size_t mid = std::min(i + blockSize / 2, n);
            size_t end = std::min(i + blockSize, n);
            size_t left = i, right = mid, idx = i;

            while (left < mid && right < end) 
            {
                if (arr[left] < arr[right])
                    temp[idx++] = arr[left++];
                else
                    temp[idx++] = arr[right++];
            }
            while (left < mid) 
                temp[idx++] = arr[left++];
            while (right < end) 
                temp[idx++] = arr[right++];

            for (size_t j = i; j < end; j++)
                arr[j] = temp[j];
        }
    }
}

void PmergeMe::mergeInsertSortVector() \
{
    printVec("vec = ", _vec);
    if (_vec.size() <= 1) 
        return ;

    bool odd = false;
    int oddValue;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> larger;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        int a = _vec[i], b = _vec[i + 1];
        if (a > b) std::swap(a, b);
        pairs.emplace_back(a, b);
        larger.push_back(b);
    }

    if (_vec.size() % 2 != 0) 
    {
        odd = true;
        oddValue = _vec.back();
    }
    printVecPairs(pairs);

    _vec = larger;
    //mergeInsertSortVector();
    printVec("larger = ", _vec);
    std::vector<int> sortedLarger = _vec;
    mergeSortedBlocks(sortedLarger); // THIS DOESN"T SEEM TO BE NEEDED?
    printVec("larger after merge = ", sortedLarger);

    std::vector<int> pendingInsertion;
    for (const auto& p : pairs) 
        pendingInsertion.push_back(p.first);
    
    printVec("pending smaller = ", pendingInsertion);

    generateJacobsthal();

    std::vector<bool> inserted(pendingInsertion.size(), false);
    for (size_t j = 0; j < _jacob.size(); j++) 
    {
        size_t idx = _jacob[j];
        if (idx >= pendingInsertion.size()) 
            break ;
        if (!inserted[idx]) 
        {
            binaryInsertVec(sortedLarger, pendingInsertion[idx]);
            inserted[idx] = true;
        }
    }

    for (size_t i = 0; i < pendingInsertion.size(); i++) 
    {
        if (!inserted[i])
            binaryInsertVec(sortedLarger, pendingInsertion[i]);
    }

    if (odd)
        binaryInsertVec(sortedLarger, oddValue);

    _vec = sortedLarger;
}

void PmergeMe::mergeInsertSortDeque()
{
    if (_deq.size() <= 1) 
        return ;
    
    //printDeq("Deque = ", _deq);

    bool    odd = false;
    int     oddValue;     

    // Step 1: Creating pairs
    std::deque<std::pair<int,int>> pairs;
    std::deque<int> larger;
    std::deque<size_t> indices;

    // Handle even-sized collection
    for (size_t i = 0; i + 1 < _deq.size(); i += 2) 
    {
        int a = _deq[i];
        int b = _deq[i + 1];
        
        // Pair with smaller element first, larger second
        pairs.emplace_back(std::min(a, b), std::max(a, b));
        larger.push_back(std::max(a, b));
        indices.push_back(i/2);
    }

    // If odd, last element goes to oddValue
    if (_deq.size() % 2 != 0)
    {
        oddValue = _deq.back();
        odd = true;
    }

    // printDeqPairs(pairs);
    // std::cout << std::endl;

    // Recursive sort
    _deq = larger;
    mergeInsertSortDeque();

     // Reconstruct pairs based on sorted larger elements
    std::deque<std::pair<int,int>> sortedPairs;
    for (size_t idx : indices)
        sortedPairs.push_back(pairs[idx]);
    pairs = sortedPairs;

    // printDeq("Sorted larger = ", _deq);
    // std::cout << "Sorted ";
    // printDeqPairs(pairs);

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
        // std::cout << "After inserting smaller (Jacobsthal " << _jacob[j] << ") " << pairs[idx].first << ": ";
        // printDeq("", _deq);
    }

    // Step 3: Insert any remaining pending elements not covered by Jacobsthal
    for (size_t i = 0; i < pairs.size(); i++) 
    {
        if (!inserted[i]) 
        {
            binaryInsertDeq(_deq, pairs[i].first, _deq.size());
            // std::cout << "After inserting smaller remaining " << pairs[i].first << ": ";
            // printDeq("", _deq);
        }
    }
    if (odd)
    {
        binaryInsertDeq(_deq, oddValue, _deq.size());
        // std::cout << "After inserting odd value " << oddValue << ": ";
        // printDeq("", _deq);
    }
    //std::cout << std::endl;
}

std::vector<int>   PmergeMe::getVec() const
{
    return (_vec);
}

std::deque<int>   PmergeMe::getDeq() const
{
    return (_deq);
}

