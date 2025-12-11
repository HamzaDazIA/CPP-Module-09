#include "PmergeMe.hpp"


int main(int ac, char **av)
{
    if (ac != 2 )
    {
        std::cerr << "Error : invalide parameter" << std::endl;
        return ;
    }
    try
    {
        PmergeMe obj;
        obj.parsing_paraneter(av[1]);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
