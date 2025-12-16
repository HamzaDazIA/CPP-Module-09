#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <climits>
#include <sys/time.h>

typedef std::vector<int> i_vector;
typedef std::vector<i_vector> g_vector;
typedef std::deque<int> i_deque;
typedef std::deque<i_deque> g_deque;



class PmergeMe
{
    private:
        i_vector cont_vector;
        i_deque cont_deque;

    public :
        PmergeMe();
        PmergeMe(const PmergeMe& obj);
        PmergeMe& operator=(const PmergeMe& obj);
        ~PmergeMe();
        void parsing_paraneter(std::string str);
        template <typename T> void running_sorting_algorithm(T & cont);
        void print_container_and_sort(bool display);
};

template <typename T> void PmergeMe::running_sorting_algorithm(T& cont)
{
    
}

#endif

