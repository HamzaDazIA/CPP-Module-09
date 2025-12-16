#include "PmergeMe.hpp"


PmergeMe::PmergeMe(){}
PmergeMe& PmergeMe::operator=(const PmergeMe & obj)
{

    return (*this);
}

PmergeMe::PmergeMe(const PmergeMe& obj)
{
    *this = obj;
}

PmergeMe::~PmergeMe(){}


void PmergeMe::parsing_paraneter(std::string str)
{
    char *end;
    long long num = std::strtoll(str.c_str(), &end, 10);
    if (*end != '\0' || num <= 0 || num > INT_MAX)
    {
        throw std::invalid_argument("Invalid input: " + str);
    }
    cont_deque.push_back(static_cast<int>(num));
    cont_vector.push_back(static_cast<int>(num));

}

void PmergeMe::print_container_and_sort(bool display)
{
    timeval start, end;
    std::vector<std::vector<int>> group_vector;
    std::deque<std::deque<int>> group_deque;
    std::vector<int>::iterator it = cont_vector.begin();
    for (; it != cont_vector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    if (display)
    {
        gettimeofday(&start, NULL);
        running_sorting_algorithm(cont_vector , group_vector);
        gettimeofday(&end, NULL);
        time_t seconds = end.tv_sec - start.tv_sec;
        time_t microseconds = end.tv_usec - start.tv_usec;
        time_t elapsed = seconds * 1000000 + microseconds;
        std::cout << "Time to process a range of " << cont_vector.size() << 
            " elements with std::vector : " << elapsed << " microseconds" << std::endl;

        gettimeofday(&start, NULL);
        running_sorting_algorithm(cont_deque , group_deque);
        gettimeofday(&end, NULL);

        seconds = end.tv_sec - start.tv_sec;
        microseconds = end.tv_usec - start.tv_usec;
        elapsed = seconds * 1000000 + microseconds;

        std::cout << "Time to process a range of " << cont_deque.size()
            << " elements with std::deque : " << elapsed << " microseconds" << std::endl;

        std::vector<int>::iterator it = cont_vector.begin();
        for (; it != cont_vector.end(); it++)
        {
            std::cout << *it << " ";
        }
    }
    
}

std::vector<size_t> generateJacobsthal(size_t pend_size)
{
    std::vector<size_t> jacobsthal;
    if (pend_size == 0)
        return jacobsthal;
    jacobsthal.push_back(0);
    if (pend_size == 1)
        return jacobsthal;
    jacobsthal.push_back(1);

    size_t pv = 0;
    size_t temp = 1;

    for (;;true)
    {
        size_t rs = pv + 2 * temp;
        if (rs >= pend_size)
            break;
        jacobsthal.push_back(rs);

        pv = temp;
        temp = rs;
    }
    return (jacobsthal);
}

std::vector<size_t> PmergeMe::get_order_jacobsthal(size_t pend_size)
{
    if (pend_size == 0)
        return std::vector<size_t>();

    std::vector<size_t> jacobsthal = generateJacobsthal(pend_size + 1);
    std::vector<size_t> order;
    size_t temp = 0;

    for (size_t i = 2; i < jacobsthal.size(); i++)
    {
        size_t curr = jacobsthal[i];
        for(size_t j = std::min(curr, pend_size); j > temp; j--)
        {
            order.push_back(j - 1);
        }
        temp = curr;
        if (temp >= pend_size)
            break;

    }

    for (size_t j = pend_size ; j > temp; j--)
    {
        order.push_back(j - 1);
    }
    return (order);
}

