#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    std::vector<std::vector<unsigned int>>   seq;

    for (int i = 1; i < argc; i++)
    {
        try
        {
            unsigned int num1 = std::stoi(argv[i]);
            unsigned int num2 = (i + 1 < argc) ? std::stoi(argv[i + 1]) : 0;
            seq.push_back({num1, num2});
            if (i + 1 < argc)
                i++;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    std::cout << "Sequence:" << std::endl;
    for (const auto& pair : seq) 
    {
        std::cout << "[" << pair[0] << ", " << pair[1] << "]" << std::endl;
    }
}