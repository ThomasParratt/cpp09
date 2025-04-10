#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe& obj) : _vec(obj._vec), _deq(obj._deq)
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
        _vec = obj._vec;
        _deq = obj._deq;
    }
    return (*this);
}
        
PmergeMe::~PmergeMe()
{

}

// void PmergeMe::generateJacobsthal() 
// {
//     _jacob.push_back(1);
//     _jacob.push_back(2);

//     // Generate the sequence until it covers the necessary size
//     while (_jacob.back() <= _vec.size()) {
//         size_t nextValue = 2 * _jacob.back() + _jacob[_jacob.size() - 2];
//         _jacob.push_back(nextValue);
//     }
// }

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

// void PmergeMe::binaryInsertVec(std::vector<int>& arr, int value) 
// {
//     auto pos = std::lower_bound(arr.begin(), arr.end(), value);
//     arr.insert(pos, value);
// }

// void PmergeMe::binaryInsertDeq(std::deque<int>& sorted, int value, size_t idx)
// {
//     auto pos = std::lower_bound(sorted.begin(), sorted.begin() + idx + 1, value);
//     sorted.insert(pos, value);
// }

// void PmergeMe::mergeSortedBlocks(std::vector<int>& arr) 
// {
//     size_t n = arr.size();
//     std::vector<int> temp(arr.size());
//     for (size_t blockSize = 2; blockSize / 2 < n; blockSize *= 2)
//     {
//         std::cout << "Block size = " << blockSize << std::endl;
//         printVec("arr = ", arr);
//         for (size_t i = 0; i < n; i += blockSize)
//         {
//             size_t mid = std::min(i + blockSize / 2, n);
//             size_t end = std::min(i + blockSize, n);
//             size_t left = i, right = mid, idx = i;

//             while (left < mid && right < end)
//             {
//                 if (arr[left] < arr[right])
//                     temp[idx++] = arr[left++];
//                 else
//                     temp[idx++] = arr[right++];
//             }
//             while (left < mid) 
//                 temp[idx++] = arr[left++];
//             while (right < end) 
//                 temp[idx++] = arr[right++];

//             for (size_t j = i; j < end; j++)
//                 arr[j] = temp[j];
//         }
//     }
// }

// void PmergeMe::binaryInsertLimited(std::vector<int>& sorted, int value, int limitValue) 
// {
//     size_t left = 0;
//     size_t right = sorted.size();

//     // Find the upper bound (index of limitValue)
//     for (size_t i = 0; i < sorted.size(); ++i) 
//     {
//         if (sorted[i] == limitValue) 
//         {
//             right = i;
//             break ;
//         }
//     }

//     // Standard binary search within [left, right)
//     while (left < right) 
//     {
//         size_t mid = (left + right) / 2;
//         if (value < sorted[mid])
//             right = mid;
//         else
//             left = mid + 1;
//     }

//     sorted.insert(sorted.begin() + left, value);
// }

std::vector<size_t>	PmergeMe::generateJacobsthal(size_t pairSize)
{
	std::vector<size_t>	seq;
	size_t				num;

	seq.push_back(1);
	seq.push_back(3);

	num = 3;
	for(int i = 2; num < pairSize; i++)
	{
		num = seq[i - 1] + 2 * seq[i - 2];
		seq.push_back(num);
	}
	return (seq);
}

size_t	PmergeMe::findPartner(size_t a, std::vector<std::pair<int, int>>& pairs)
{
	for (std::pair<size_t, size_t> p : pairs)
	{
		if (a == p.second)
		{
			//std::cout <<  "Found pair value  (" << p.first  << ", " << p.second << ")" <<  std::endl;
			return (p.first);
		}
	}
	return (0);
}

void	PmergeMe::insertion(std::vector<int>& main, std::vector<std::pair<int, int>>& pairs)
{
	std::vector<size_t> jacobSeq;

	jacobSeq = generateJacobsthal(pairs.size());

	std::vector<int> mainBeforeInsertion = main;

	size_t value = findPartner(main[0], pairs);	//Find b1
    std::cout << "Inserting " << value << " to front" << std::endl;
	main.insert(main.begin(), value);			//Insert to front -> b1, a1, a2, a3...
    printVec("main = ", main);

	if (pairs.size() == 1)						//All values added from pairs.
		return ;

	for (size_t i = 1; i < jacobSeq.size(); i++)
	{
		size_t curr = jacobSeq[i];
		size_t prev = jacobSeq[i-1];


		for (size_t i = curr; i != prev; i--)	// Going reverse order (f.ex. 3, 2 OR 5, 4 OR 11, 10, 9, 8, 7, 6 OR etc)
		{
            printVec("main = ", main);
            printVec("main copy = ", mainBeforeInsertion);
            std::cout << "Index = " << i << std::endl;
			if (i > pairs.size()) // Checks if index out of bounds
				continue ;

			// Find Corresponding b value
			size_t value = findPartner(mainBeforeInsertion[i - 1], pairs);
			
			// Find Position to insert
			auto pos = std::lower_bound(main.begin(), main.end(), value); 

			// Insert
            std::cout << "Inserting " << value << " using binary insert" << std::endl;
			main.insert(pos, value);
            printVec("main = ", main);
		}
	}
}

void PmergeMe::mergeInsertSortVector()
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
    }
    printVecPairs(pairs);

    _vec = larger;
    printVec("larger = ", _vec);
    std::cout << std::endl;
    mergeInsertSortVector();
    //std::vector<int> sortedLarger = _vec;
    //mergeSortedBlocks(sortedLarger);
    std::cout << std::endl;
    printVec("larger/main = ", _vec);
    printVecPairs(pairs);

    //5. Binary Insertion
	insertion(_vec, pairs);


	// Step 7: Insert the odd element, if there is one
    if (odd)
    {
		auto pos = std::lower_bound(_vec.begin(), _vec.end(), oddValue); 
		_vec.insert(pos, oddValue);
    }

	// 7. Assign to vector
	//vec = larger_numbers;

    // // Step 3: Prepare the pending smaller elements (pendingInsertion)
    // std::vector<int> pendingInsertion;
    // for (const auto& p : pairs)
    //     pendingInsertion.push_back(p.first);
    // printVec("pending smaller = ", pendingInsertion);

    // // Step 4: Generate the Jacobsthal sequence
    // generateJacobsthal();

    // // Step 5: Insert smaller elements from pendingInsertion using Jacobsthal sequence
    // std::vector<bool> inserted(pendingInsertion.size(), false);
    // for (size_t j = 0; j < _jacob.size(); j++) 
    // {
    //     size_t idx = _jacob[j];
    //     if (idx >= pendingInsertion.size()) 
    //         break; // If we're past the pendingInsertion, stop

    //     if (!inserted[idx]) 
    //     {
    //         // Insert using binary search, limited by the value of its pair (a#)
    //         binaryInsertLimited(sortedLarger, pendingInsertion[idx], larger[idx]);
    //         inserted[idx] = true;  // Mark this element as inserted
    //     }
    // }

    // // Step 6: Insert any remaining smaller elements
    // for (size_t i = 0; i < pendingInsertion.size(); i++) 
    // {
    //     if (!inserted[i])
    //         binaryInsertLimited(sortedLarger, pendingInsertion[i], sortedLarger.back());
    // }

    // // Step 7: Insert the odd element, if there is one
    // if (odd)
    //     binaryInsertLimited(sortedLarger, oddValue, sortedLarger.back());

    // // Final sorted sequence
    // _vec = sortedLarger;
    // printVec("sorted = ", _vec);
}

// void PmergeMe::mergeInsertSortDeque()
// {
//     if (_deq.size() <= 1) 
//         return ;
    
//     //printDeq("Deque = ", _deq);

//     bool    odd = false;
//     int     oddValue;     

//     // Step 1: Creating pairs
//     std::deque<std::pair<int,int>> pairs;
//     std::deque<int> larger;
//     std::deque<size_t> indices;

//     // Handle even-sized collection
//     for (size_t i = 0; i + 1 < _deq.size(); i += 2) 
//     {
//         int a = _deq[i];
//         int b = _deq[i + 1];
        
//         // Pair with smaller element first, larger second
//         pairs.emplace_back(std::min(a, b), std::max(a, b));
//         larger.push_back(std::max(a, b));
//         indices.push_back(i/2);
//     }

//     // If odd, last element goes to oddValue
//     if (_deq.size() % 2 != 0)
//     {
//         oddValue = _deq.back();
//         odd = true;
//     }

//     // printDeqPairs(pairs);
//     // std::cout << std::endl;

//     // Recursive sort
//     _deq = larger;
//     mergeInsertSortDeque();

//      // Reconstruct pairs based on sorted larger elements
//     std::deque<std::pair<int,int>> sortedPairs;
//     for (size_t idx : indices)
//         sortedPairs.push_back(pairs[idx]);
//     pairs = sortedPairs;

//     // printDeq("Sorted larger = ", _deq);
//     // std::cout << "Sorted ";
//     // printDeqPairs(pairs);

//     // Step 2: Insert pending elements using Jacobsthal sequence
//     std::deque<bool> inserted(pairs.size(), false);

//     for (size_t j = 0; j < _jacob.size(); j++) 
//     {
//         size_t idx = _jacob[j];
//         if (idx >= pairs.size())
//             break ;
//         if (inserted[idx])
//             continue ;
//         binaryInsertDeq(_deq, pairs[idx].first, idx);
//         inserted[idx] = true;
//         // std::cout << "After inserting smaller (Jacobsthal " << _jacob[j] << ") " << pairs[idx].first << ": ";
//         // printDeq("", _deq);
//     }

//     // Step 3: Insert any remaining pending elements not covered by Jacobsthal
//     for (size_t i = 0; i < pairs.size(); i++) 
//     {
//         if (!inserted[i]) 
//         {
//             binaryInsertDeq(_deq, pairs[i].first, _deq.size());
//             // std::cout << "After inserting smaller remaining " << pairs[i].first << ": ";
//             // printDeq("", _deq);
//         }
//     }
//     if (odd)
//     {
//         binaryInsertDeq(_deq, oddValue, _deq.size());
//         // std::cout << "After inserting odd value " << oddValue << ": ";
//         // printDeq("", _deq);
//     }
//     //std::cout << std::endl;
// }

std::vector<int>   PmergeMe::getVec() const
{
    return (_vec);
}

std::deque<int>   PmergeMe::getDeq() const
{
    return (_deq);
}

