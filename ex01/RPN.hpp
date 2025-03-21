#include <iostream>
#include <stack>

class RPN
{
    private:
        std::string _input;
    public:
        RPN() = delete;
        RPN(const RPN& obj);
        RPN(std::string input);
        RPN& operator=(const RPN& obj);
        ~RPN();
        void    parseInput();
};