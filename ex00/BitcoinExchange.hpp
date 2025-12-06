#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#include <cstring>
#include <string> // Added for std::string

#define CSV_FILE "data.csv"
#define CONVER 10
#define UNCONVER 20
#define PIPE 124
#define COMMA 44

class BitcoinExchange
{
    private : 
        std::map<time_t , double> cont_map;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange & operator=(const BitcoinExchange& obj);
        void read_stord_cvs(void);
        void   parsing_date(std::string str);
        void convert_time(int year, int month, int day,  double key_value);
        std::string unconvert_time(time_t timestamp);
        std::string find_key(std::string str);
    
};


#endif