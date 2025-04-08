#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "Error: Program has no arguments" << std::endl;
        exit(1);
    }
    PmergeMe sorter = PmergeMe(argc, argv);

    // sorter.printVec("Before: ", sorter.getVec());
    // auto start = std::chrono::high_resolution_clock::now();
    // sorter.fordJohnsonSort();
    // auto end = std::chrono::high_resolution_clock::now();
    // sorter.printVec("After:  ", sorter.getVec());
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << "Time to process a range of " << sorter.getVec().size() << " elements with std::vector: " << duration.count() << " us\n";

    sorter.printVec("Before: ", sorter.getVec());
    auto start = std::chrono::high_resolution_clock::now();
    sorter.mergeInsertSortVector();
    auto end = std::chrono::high_resolution_clock::now();
    sorter.printVec("After:  ", sorter.getVec());
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time to process a range of " << sorter.getVec().size() << " elements with std::vector: " << duration.count() << " us\n";

    // //sorter.printDeq("Before: ", sorter.getDeq());
    // start = std::chrono::high_resolution_clock::now();
    // sorter.mergeInsertSortDeque();
    // end = std::chrono::high_resolution_clock::now();
    // //sorter.printDeq("After:  ", sorter.getDeq());
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout << "Time to process a range of " << sorter.getDeq().size() << " elements with std::deque:  " << duration.count() << " us\n";
}