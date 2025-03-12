#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    std::vector<std::pair<unsigned int, unsigned int>> _seq;

    for (int i = 1; i < argc; i+=2)
    {
        if (i + 1 < argc)
            _seq.push_back(std::make_pair(std::stoul(argv[i]), std::stoul(argv[i + 1])));
        else
            _odd = std::stoul(argv[i]);
    }

    for (auto &p : _seq)
    {
        std::cout << "First: " << p.first << ", Second: " << p.second << std::endl;
    }
    std::cout << "First: " << _odd << std::endl;
}