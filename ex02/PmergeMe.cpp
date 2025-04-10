#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& obj) : _vec(obj._vec), _deq(obj._deq) {}

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
        _vec = obj._vec;
        _deq = obj._deq;
    }
    return (*this);
}
        
PmergeMe::~PmergeMe() {}

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

std::vector<size_t>	PmergeMe::generateJacobsthal(size_t pairSize)
{
	std::vector<size_t> seq;
    seq.push_back(1);
    while (seq.back() < pairSize)
    {
        size_t next = seq.size() < 2 ? 3 : seq.back() + 2 * seq[seq.size() - 2];
        seq.push_back(next);
    }
    return (seq);
}

size_t	PmergeMe::findVecPartner(size_t largerValue, std::vector<std::pair<int, int>>& pairs)
{
	for (std::pair<int, int> p : pairs)
	{
		if (largerValue == p.second)
			return (p.first);
	}
	return (0);
}

size_t	PmergeMe::findDeqPartner(size_t largerValue, std::deque<std::pair<int, int>>& pairs)
{
	for (std::pair<int, int> p : pairs)
	{
		if (largerValue == p.second)
			return (p.first);
	}
	return (0);
}

void	PmergeMe::insertionVec(std::vector<int>& sorted, std::vector<std::pair<int, int>>& pairs)
{
	std::vector<size_t> jacobSeq;

	jacobSeq = generateJacobsthal(pairs.size());

	std::vector<int> sortedBeforeInsertion = sorted;

	size_t value = findVecPartner(sorted[0], pairs);
    //std::cout << "Inserting " << value << " to front" << std::endl;
	sorted.insert(sorted.begin(), value);
    //printVec("sorted = ", sorted);

	if (pairs.size() == 1)
		return ;

	for (size_t i = 1; i < jacobSeq.size(); i++)
	{
		size_t curr = jacobSeq[i];
		size_t prev = jacobSeq[i-1];

        //std::cout << "i = " << i << std::endl;
        //std::cout << "curr = " << curr << ", prev = " << prev << std::endl; 

		for (size_t j = curr; j != prev; j--)
		{
            if (j > pairs.size())
				continue ;

            //std::cout << "j (iterate from curr to one above prev) = " << j << std::endl;

			size_t value = findVecPartner(sortedBeforeInsertion[j - 1], pairs);

			auto pos = std::lower_bound(sorted.begin(), sorted.end(), value); 
            //std::cout << "Inserting " << value << std::endl;
			sorted.insert(pos, value);
            //printVec("sorted = ", sorted);
		}
        //std::cout << std::endl;
	}
}

void	PmergeMe::insertionDeq(std::deque<int>& sorted, std::deque<std::pair<int, int>>& pairs)
{
	std::vector<size_t> jacobSeq;

	jacobSeq = generateJacobsthal(pairs.size());

	std::deque<int> sortedBeforeInsertion = sorted;

	size_t value = findDeqPartner(sorted[0], pairs);
	sorted.insert(sorted.begin(), value);

	if (pairs.size() == 1)
		return ;

	for (size_t i = 1; i < jacobSeq.size(); i++)
	{
		size_t curr = jacobSeq[i];
		size_t prev = jacobSeq[i-1];

		for (size_t j = curr; j != prev; j--)
		{
			if (j > pairs.size())
				continue ;

			size_t value = findDeqPartner(sortedBeforeInsertion[j - 1], pairs);
			auto pos = std::lower_bound(sorted.begin(), sorted.end(), value);
			sorted.insert(pos, value);
		}
	}
}

void PmergeMe::mergeInsertSortVector()
{
    //printVec("vec = ", _vec);
    if (_vec.size() <= 1) 
        return ;

    bool odd = false;
    int oddValue;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> larger;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) 
    {
        int a = _vec[i]; 
        int b = _vec[i + 1];
        if (a > b) 
            std::swap(a, b);
        pairs.emplace_back(a, b);
        larger.push_back(b);
    }

    if (_vec.size() % 2 != 0) 
    {
        odd = true;
        oddValue = _vec.back();
        //std::cout << "odd value = " <<  oddValue << std::endl;
    }
    //printVecPairs(pairs);

    _vec = larger;
    //printVec("larger = ", _vec);
    //std::cout << std::endl;
    mergeInsertSortVector();
    //std::cout << std::endl << std::endl;
    //printVec("SORTED = ", _vec);
    //printVecPairs(pairs);

	insertionVec(_vec, pairs);

    if (odd)
    {
		auto pos = std::lower_bound(_vec.begin(), _vec.end(), oddValue);
        //std::cout << "Inserting odd " << oddValue << std::endl;
		_vec.insert(pos, oddValue);
        //printVec("sorted = ", _vec);
    }
}

void PmergeMe::mergeInsertSortDeque()
{
    if (_deq.size() <= 1) 
        return ;

    bool odd = false;
    int oddValue;
    std::deque<std::pair<int, int>> pairs;
    std::deque<int> larger;

    for (size_t i = 0; i + 1 < _deq.size(); i += 2) 
    {
        int a = _deq[i]; 
        int b = _deq[i + 1];
        if (a > b) 
            std::swap(a, b);
        pairs.emplace_back(a, b);
        larger.push_back(b);
    }

    if (_deq.size() % 2 != 0) 
    {
        odd = true;
        oddValue = _deq.back();
    }

    _deq = larger;
    mergeInsertSortDeque();

	insertionDeq(_deq, pairs);

    if (odd)
    {
		auto pos = std::lower_bound(_deq.begin(), _deq.end(), oddValue); 
		_deq.insert(pos, oddValue);
    }
}

std::vector<int>   PmergeMe::getVec() const
{
    return (_vec);
}

std::deque<int>   PmergeMe::getDeq() const
{
    return (_deq);
}

