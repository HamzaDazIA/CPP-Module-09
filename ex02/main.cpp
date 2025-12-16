#include "PmergeMe.hpp"

int main(int ac , char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: No input provided" << std::endl;
        std::cerr << "Usage: ./PmergeMe <positive integers...>" << std::endl;
        return 1;
    }
    PmergeMe pmergeme;
    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        try
        {
            pmergeme.parsing_paraneter(arg);
        }

        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }

    pmergeme.print_container_and_sort(true);
    pmergeme.print_container_and_sort(false);
    return 0;

}