#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <climits>
#include <sys/time.h>
#include <algorithm>
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
        template <typename T ,typename TG> void ford_Johson_algo(TG & group, T& cont);
        std::vector<size_t> get_order_jacobsthal(size_t pend_size);

};

template <typename T , typename TG>void PmergeMe::running_sorting_algorithm(T& cont, TG & group)
{
    for (; T::iterator it = cont.begin(); it != cont.end(); it++)
    {
        T temp.push_back(*it);
        group.push_back(temp);
    }

    ford_Johson_algo(group, cont);
}

template <typename T ,typename TG> void PmergeMe::ford_Johson_algo(TG &group , T& cont)
{
    (void) cont
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

    TG temp;
    for (size_t i = 0; i + 1 < group.size(); i += 2)
    {
        T a = group[i];
        T b = group[i + 1];
        if (a < b)
        {
            std::swap(a, b)
        }
        a.insert(a.end(), b.begin(), b.end());
        ten.push_back(a);
    }
    group = temp;
    ford_Johson_algo(group, cont);

    size_t pair_size = group.front().size() / 2;
    TG main_chain;
    TG pend_chain;

    for (size_t i = 0; i < group.size(); i++)
    {
        T winners(group[i].begin(), group[i].begin() + pair_size);
        main_chain.push_back(winners);
        T losers(group[i].begin() + pair_size , group[i].end());
        pend_chain.push_back(losers);
    }

    if (!pend_chain.empty())
        main_chain.insert(main_chain.begin(), pend_chain[0]);
    
    std::vector<int> sequence_order = get_order_jacobsthal(pend.size());
    // Insertion phase know we have orders so we can insert take elements from pend chain and insert them into main chain
}

#endif

