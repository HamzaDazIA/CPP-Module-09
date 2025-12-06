#include "BitcoinExchange.hpp"


int main()
{
    BitcoinExchange btc;
    try
    {
        btc.read_stord_cvs();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}