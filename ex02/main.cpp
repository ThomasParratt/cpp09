#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "Error: Program has no arguments" << std::endl;
        exit(1);
    }
    PmergeMe sorter = PmergeMe(argc, argv);

    sorter.printVec("Before: ", sorter.getVec());
    auto start = std::chrono::high_resolution_clock::now();
    sorter.mergeInsertSort();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time to process a range of " << sorter.getVec().size() << " elements with std::vector: " << duration.count() << " us\n";
    sorter.printVec("After:  ", sorter.getVec());
}