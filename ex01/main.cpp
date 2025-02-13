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