#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>
#include <deque>
typedef std::vector<int> i_vector;
typedef std::vector<i_vector> vv_vector;



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

