#include "RPN.hpp"

RPN::RPN() : _input("")
{

}

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
    
    if (_input.empty())
    {
        std::cerr << "Error: Missing input" << std::endl;
        return ;
    }
    for (size_t i = 0; i < _input.size(); i++)
    {
        char c = _input[i];
            
        if (isdigit(c))
        {
            std::string num_str = "";
            
            // Collect the entire number
            while (i < _input.size() && isdigit(_input[i]))
            {
                num_str += _input[i];
                i++;
            }
            i--;

            int num = std::stoi(num_str);
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
    
            switch (c)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
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
        else if (c != ' ')  // Handle invalid characters
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
