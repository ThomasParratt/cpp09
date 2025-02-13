#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    std::vector<std::vector<unsigned int>>   seq;

    for (int i = 1; i < argc; i++)
    {
        try
        {
            unsigned int num1 = std::stoul(argv[i]);
            if (i + 1 < argc)
            {
                unsigned int num2 = std::stoul(argv[i + 1]);
                seq.push_back({num1, num2});
                i++;
            }
            else
                seq.push_back({num1});
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    std::cout << "Sequence:" << std::endl;
        for (const auto &pair : seq) 
        {
            std::cout << "[";
            for (size_t j = 0; j < pair.size(); j++) 
            {
                std::cout << pair[j];
                if (j + 1 < pair.size()) std::cout << ", ";
            }
            std::cout << "]" << std::endl;
        }
}