#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<unsigned int> sequence) : _seq(sequence)
{
    for (auto &it : _seq)
        std::cout << it << std::endl;
}