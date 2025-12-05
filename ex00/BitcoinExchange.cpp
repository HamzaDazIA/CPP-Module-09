
#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(){
}

BitcoinExchange::BitcoinExchange(const  BitcoinExchange& obj)
{

}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &obj)
{

}

void BitcoinExchange::read_stord_cvs(void)
{
    std::ifstream file_csv("data.csv");
    if (!file_csv)
        throw(std::runtime_error("Failed to open file"));
    std::string line;

    while(getline(file_csv, line))
    {
        this->parsing_date(line);
    }
}

void   BitcoinExchange::parsing_date(std::string str)
{
    const char *fnd = "-";
    if (str.size() < 10)
        throw(std::runtime_error("Error: bad date format"));

    char str_copy[100];
    strcpy(str_copy, str.c_str());
    long long year;
    long long month;
    long long day;

    char *t = strtok(str_copy, fnd);
    int i = 0;
    while(t != nullptr) {
        if (i == 0)
            year = std::strtoll(t, nullptr, 10);
        else if (i == 1)
            month = std::strtoll(t, nullptr, 10);
        else if (i == 2)
            day = std::strtoll(t, nullptr, 10);
        t = strtok(nullptr, fnd);
        i++;
    }
    if (i != 3)
        throw(std::runtime_error("Error: bad date format"));
    if (year > 9999 || month > 12 || day > 31 || year < 0 || month < 1 || day < 1)
        throw(std::runtime_error("Error: bad date format"));

    convert_unconvert_time(static_cast<int> (year), static_cast<int> (month), static_cast<int> (day), CONVER);
    
}


void BitcoinExchange::convert_unconvert_time(int year, int month, int day, int flag)
{
    this->cont_map.clear();
    
}
