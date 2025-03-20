#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN <arg>" << std::endl;
        exit(1);
    }
    RPN rpn = RPN(argv[1]);
    rpn.parseInput();
}

// Order of operations
// "2 3 * 4 + 5 *"
// "3 2 * 5 3 * + 9 -"