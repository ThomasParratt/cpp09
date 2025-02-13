#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
    // std::vector<unsigned int> seq;

    // for (int i = 1; i < argc; i++)
    // {
    //     try
    //     {
    //         seq.push_back(std::stoul(argv[i]));
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << std::endl;
    //     }
    // }

    // std::cout << "Sequence:" << std::endl;
    // for (auto &it : seq)
    //     std::cout << it << std::endl;

    // SORTING INTO 2D VECTOR OF PAIRS
    std::vector<std::vector<unsigned int>>   seq;

    for (int i = 1; i < argc; i++)
    {
        try
        {
            unsigned int num1 = std::stoul(argv[i]);
            if (i + 1 < argc)
            {
                unsigned int num2 = std::stoul(argv[i + 1]);
                (num1 < num2) ? seq.push_back({num1, num2}) : seq.push_back({num2, num1});
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
            std::cout << pair[j];
        std::cout << "] ";
    }
    std::cout << std::endl;
}