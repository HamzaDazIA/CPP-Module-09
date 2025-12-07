#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>


class RPN
{
    private:
        std::stack<int>  cont_stack;
    
    public:
        RPN();
        RPN(const RPN& obj);
        RPN & operator=(const RPN &obj);
        void calculate(const std::string &str);
        ~RPN();
};


#endif
