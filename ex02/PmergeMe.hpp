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



class PmergeMe
{
    private:
        std::vector<int> cont_vector;
        std::deque<int> cont_deque;

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
        template <typename TG, typename T> size_t binarySearchLimited(const TG& main_chain, const T& target, size_t limit);

};

template <typename T , typename TG>void PmergeMe::running_sorting_algorithm(T& cont, TG & group)
{
    for (typename T::iterator it = cont.begin(); it != cont.end(); it++)
    {
        T temp;
        temp.push_back(*it);
        group.push_back(temp);
    }

    ford_Johson_algo(group, cont);

    cont.clear();
    for (typename TG::iterator it = group.begin(); it != group.end(); ++it)
    {
        for (typename T::iterator elem = it->begin(); elem != it->end(); ++elem)
        {
            cont.push_back(*elem);
        }
    }
}

template <typename T ,typename TG> void PmergeMe::ford_Johson_algo(TG &group , T& cont)
{
    (void) cont;
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
            std::swap(a, b);
        }
        a.insert(a.end(), b.begin(), b.end());
        temp.push_back(a);
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
    
    std::vector<size_t> sequence_order = get_order_jacobsthal(pend_chain.size());
    // Insertion phase know we have orders so we can insert take elements from pend chain and insert them into main chain
    for (size_t i = 0 ; i < sequence_order.size(); i++)
    {
        size_t idx  = sequence_order[i];
        if (idx == 0 || idx >= pend_chain.size())
            continue;
        
        size_t main_idx = idx + i + 1;
        if (main_idx > main_chain.size())
            main_idx = main_chain.size();
        
        size_t insert_pos = binarySearchLimited(main_chain, pend_chain[idx], main_idx);
        main_chain.insert(main_chain.begin() + insert_pos, pend_chain[idx]);
    }
    
    if (have_straggeler)
    {
        size_t insert_pos = binarySearchLimited(main_chain, strageller, main_chain.size());
        main_chain.insert(main_chain.begin() + insert_pos, strageller);
    }
    
    group = main_chain;

}

template <typename TG, typename T>
size_t PmergeMe::binarySearchLimited(const TG& main_chain, const T& target, size_t limit)
{
    size_t left = 0;
    size_t right = limit;
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        // Compare using the first element only (the "key")
        if (main_chain[mid][0] < target[0])
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}

#endif

