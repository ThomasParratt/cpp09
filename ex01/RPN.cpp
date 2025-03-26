#include "RPN.hpp"

RPN::RPN(const RPN& obj)
{
    *this = obj;
}

RPN::RPN(std::string input) : _input(input)
{

}

RPN& RPN::operator=(const RPN& obj)
{
    if (this != &obj)
        _input = obj._input;
    return (*this);
}

RPN::~RPN()
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
                return;
            }
    
            int b = values.top();
            values.pop();
            int a = values.top();
            values.pop();
            int result;
    
            switch (c) {
                case '+':
                    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) 
                    {
                        std::cerr << "Error: Integer overflow on addition" << std::endl;
                        return ;
                    }
                    result = a + b;
                    break ;
                case '-':
                    if ((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b)) 
                    {
                        std::cerr << "Error: Integer overflow on subtraction" << std::endl;
                        return ;
                    }
                    result = a - b;
                    break ;
                case '*':
                    if (a != 0 && (b > INT_MAX / a || b < INT_MIN / a)) 
                    {
                        std::cerr << "Error: Integer overflow on multiplication" << std::endl;
                        return ;
                    }
                    result = a * b;
                    break ;
                case '/':
                    if (b == 0) 
                    {
                        std::cerr << "Error: Division by zero" << std::endl;
                        return ; 
                    }
                    if (a == INT_MIN && b == -1) 
                    {
                        std::cerr << "Error: Integer overflow on division" << std::endl;
                        return ;
                    }
                    result = a / b;
                    break ;
            }
            values.push(result);
        }
        else if (c != ' ')  // Handle invalid characters
        {
            std::cerr << "Error: Invalid input characters" << std::endl;
            return ;
        }
    }
    
    if (values.size() == 1)
        std::cout << values.top() << std::endl;
    else
        std::cerr << "Error: Invalid input" << std::endl;
}
