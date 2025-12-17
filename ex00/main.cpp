#include "BitcoinExchange.hpp"


int main(int ac , char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: you need file .txt ." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    try
    {
        btc.read_stord_cvs();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    btc.read_file_input(av[1]);
    return 0;
}