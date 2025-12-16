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
        template <typename T , typename TG> void running_sorting_algorithm(T & cont , TG & group);
        void print_container_and_sort(bool display);
        template <typename T ,typename TG> void ford_Johson_algo(TG & group);
};

template <typename T , typename TG>void PmergeMe::running_sorting_algorithm(T& cont, TG & group)
{
    for (; T::iterator it = cont.begin(); it != cont.end(); it++)
    {
        T temp.push_back(*it);
        group.push_back(temp);
    }

    ford_Johson_algo(group);
}

template <typename T ,typename TG> void PmergeMe::ford_Johson_algo(TG &group )
{
    size_t size =  group.size();
    if (size <= 1)
        return ;
    T strageller;
    bool have_straggeler = false;
    if (size % 2 == 1)
    {
        strageller = group.back();
        group.pop_back();
        have_straggeler = true;
    }

    


}

#endif

