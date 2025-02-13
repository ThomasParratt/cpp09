#include <iostream>
#include <stack>

class RPN
{
    private:
        std::string _input;
    public:
        RPN(std::string input);
        void    parseInput();
};