#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#include <cstring>

#define CSV_FILE "data.csv"
#define CONVER 10
#define UNCONVER 20

class BitcoinExchange
{
    private : 
        std::map<size_t , int> cont_map;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange & operator=(const BitcoinExchange& obj);
        void read_stord_cvs(void);
        void   parsing_date(std::string str);
        void convert_unconvert_time(int year, int month, int day, int flag);

};

#endif