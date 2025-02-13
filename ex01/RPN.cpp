#include "RPN.hpp"

RPN::RPN(std::string input) : _input(input)
{

}

void RPN::parseInput()
{
    std::stack<int> values;

    for (char c : _input)
    {
        if (isdigit(c))
        {
            int num = c - '0'; 
            values.push(num);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (values.size() < 2)
            {
                std::cerr << "Error: Not enough operands" << std::endl;
                return ;
            }

            int b = values.top(); 
            values.pop();
            int a = values.top(); 
            values.pop();
            int result;

            switch (c)
            {
                case '+': 
                    result = a + b; 
                    break ;
                case '-': 
                    result = a - b; 
                    break ;
                case '*': 
                    result = a * b;
                    break ;
                case '/': 
                    if (b == 0)
                    {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return ;
                    }
                    result = a / b;
                    break ;
            }
            values.push(result);
        }
        else if (c != ' ')
        {
            std::cerr << "Error: Invalid input" << std::endl;
            return ;
        }
    }

    if (values.size() == 1)
        std::cout << values.top() << std::endl;
    else
        std::cerr << "Error: Invalid RPN expression" << std::endl;
}