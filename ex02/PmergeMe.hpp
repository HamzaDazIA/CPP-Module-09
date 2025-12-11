#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>


class PmergeMe
{
    private:
        std::vector<int> cont_vector;
    public :
        PmergeMe();
        PmergeMe(const PmergeMe& obj);
        PmergeMe& operator=(const PmergeMe& obj);
        ~PmergeMe();
        void parsing_paraneter(std::string str);
};

#endif

