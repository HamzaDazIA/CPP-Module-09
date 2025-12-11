#include "PmergeMe.hpp"


PmergeMe::PmergeMe(){}
PmergeMe& PmergeMe::operator=(const PmergeMe & obj)
{
    this->cont_vector = obj.cont_vector;
    return (*this);
}

PmergeMe::PmergeMe(const PmergeMe& obj)
{
     this->cont_vector = obj.cont_vector;
}

PmergeMe::~PmergeMe(){}


void PmergeMe::parsing_paraneter(std::string str)
{
    
}
