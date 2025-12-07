#ifndef BitcoinExchange_HPP
#define BitcoinExchange_HPP

#include <sstream>
#include <iostream>
#include <map>
#include <ctime>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>

#define CSV_FILE "data.csv"
#define CONVER 10
#define UNCONVER 20
#define PIPE 124
#define COMMA 44
#define MIN_YEAR 2009
#define MIN_MONTH 1
#define ERROR 404
#define MAX_YEAR 2025 
#define MAX_MONTH 12
#define CHECK 20
class BitcoinExchange
{
    private : 
        std::map<time_t , double> cont_map;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& obj);
        BitcoinExchange & operator=(const BitcoinExchange& obj);
        ~BitcoinExchange();
        void read_stord_cvs(void);
        void   parsing_date(std::string str);
        void convert_time(int year, int month, int day,  double key_value);
        std::string unconvert_time(time_t timestamp);
        std::string find_key(std::string str);

        //input.txt functions
        void read_file_input(std::string file_name);
        time_t check_date(std::string date);
        time_t convert_date_time(int year, int month, int day);
};


#endif