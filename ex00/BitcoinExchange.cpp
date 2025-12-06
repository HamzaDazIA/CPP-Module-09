
#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(){
}

BitcoinExchange::BitcoinExchange(const  BitcoinExchange& obj)
{

}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    return (*this);
}

void BitcoinExchange::read_stord_cvs(void)
{
    std::ifstream file_csv("data.csv");
    if (!file_csv)
        throw(std::runtime_error("Failed to open file"));
    std::string line;

    getline(file_csv, line);
    while(getline(file_csv, line))
    {
        this->parsing_date(line);
    }
    std::map<time_t , double>::const_iterator it;

    for (it = this->cont_map.begin(); it != this->cont_map.end(); ++it)
    {
        std::cout << unconvert_time(it->first) << " => " << it->second << std::endl;
    }
}

std::string ft_get_line_trim(std::string str) 
{
    size_t start = 0;
    size_t end = str.length() - 1;
    
    while (start <= end && std::isspace(str[start]))
        start++;
    while (end > start && std::isspace(str[end]))
        end--;
    
    if (start > end)
        return "";
    
    return str.substr(start, end - start + 1);
}

std::string BitcoinExchange::find_key(std::string str)
{
    size_t pos  = str.find_first_of(",");
    if (pos == std::string::npos)
        throw(std::runtime_error("Error: bad date format key"));
    return (str.substr(pos + 1, str.size() - pos - 1));
}

void   BitcoinExchange::parsing_date(std::string str)
{

    str = ft_get_line_trim(str);
    std::string key = find_key(str);

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
            year = std::strtoll(ft_get_line_trim(t).c_str(), nullptr, 10);
        else if (i == 1)
            month = std::strtoll(ft_get_line_trim(t).c_str(), nullptr, 10);
        else if (i == 2)
            day = std::strtoll(ft_get_line_trim(t).c_str(), nullptr, 10);
        t = strtok(nullptr, fnd);
        i++;
    }
    if (i != 3)
        throw(std::runtime_error("Error: bad date format date"));
    if (year > 9999 || month > 12 || day > 31 || year < 0 || month < 1 || day < 1)
        throw(std::runtime_error("Error: bad date format value"));
    char *endptr;
    double key_value = std::strtod(ft_get_line_trim(key).c_str(), &endptr);
    if (*endptr != '\0')
        throw(std::runtime_error("Error: invalid value"));
    convert_time(static_cast<int> (year), static_cast<int> (month),
        static_cast<int> (day),  key_value);

}


void BitcoinExchange::convert_time(int year, int month, int day, double key_value)
{
    struct tm t;
    std::memset(&t, 0, sizeof(t)); 
    
    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = day;


        time_t timestamp = std::mktime(&t);
        this->cont_map.insert(std::make_pair((timestamp), (key_value)));
}

std::string BitcoinExchange::unconvert_time(time_t timestamp)
{
    struct tm *back = std::localtime(&timestamp);
    int y = back->tm_year + 1900;
    int m = back->tm_mon + 1;
    int d = back->tm_mday;

    std::ostringstream oss;

    oss << y << "-"
        << std::setw(2) << std::setfill('0') << m << "-"
        << std::setw(2) << std::setfill('0') << d;
    return oss.str();

}
