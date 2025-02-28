#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    std::vector<std::variant<std::pair<unsigned int, unsigned int>, unsigned int>> _seq;

    for (int i = 1; i < argc; i+=2)
    {
        if (!(i + 1))
        {
            _seq.push_back(std::stoul(argv[i]));
            break ;
        }
        _seq.push_back(std::make_pair(std::stoul(argv[i]), std::stoul(argv[i + 1])));
    
    }
  
}