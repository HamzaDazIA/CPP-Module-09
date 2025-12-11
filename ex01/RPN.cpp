#include    "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& obj)
{
    *this = obj;
}

RPN & RPN::operator=(const RPN &obj)
{
    if (this != &obj)
        this->cont_stack = obj.cont_stack;
    return (*this);
}

RPN::~RPN()
{
}

void RPN::calculate(const std::string &str)
{
    if (str.empty())
    {
        std::cerr << "Error" << std::endl;
        return;
    }
    long long first ;
    long long second;
    long long rs;
    for(int i = 0; str[i]; i++)
    {

        if (!std::isdigit(str[i]) && !std::isspace(str[i]) &&  ((str[i] != '+') && str[i] != '-' && str[i] != '*' && str[i] != '/'))
        {
            std::cerr << "Error";
            return ;
        }
        if (str[i] == ' ')
            continue;
        if(std::isdigit(str[i]))
        {
            this->cont_stack.push(str[i] - '0');
            continue;
        }
        
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if(this->cont_stack.size() < 2)
            {
                std::cerr << "Error";
                return;
            }
            else
            {
                first = static_cast<long long>(this->cont_stack.top());
                this->cont_stack.pop();
                second = static_cast<long long>(this->cont_stack.top());
                this->cont_stack.pop();
                if(str[i] == '+')
                {
                    rs = first + second;
                    this->cont_stack.push(rs);
                    continue;
                }
                else if (str[i] == '-')
                {
                    rs = second - first;
                    this->cont_stack.push(rs);
                }
                else if (str[i] == '/')
                {
                    if (first == 0)
                    {
                        std::cerr << "Error";
                        return ;
                    }
                    rs = second / first;
                    this->cont_stack.push(rs);
                    continue;
                }
                else if (str[i] == '*')
                {
                    rs = second * first;
                    this->cont_stack.push(rs);
                    continue;
                }
                else 
                {
                    std::cerr << "Error";
                    return;
                }
            }
        }
    }
    if (this->cont_stack.size() != 1)
    {
        std::cerr << "Error";
        return ;
    }
    std::cout << this->cont_stack.top() ;
    return ;
}