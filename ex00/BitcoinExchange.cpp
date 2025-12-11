
#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const  BitcoinExchange& obj)
{
    *this = obj;
}



BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    if (this != &obj)
    {
        this->cont_map = obj.cont_map;
    }
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{}

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

    // for (it = this->cont_map.begin(); it != this->cont_map.end(); ++it)
    // {
    //     std::cout << unconvert_time(it->first) << " => " << it->second << std::endl;
    // }
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
    if (year > MAX_YEAR || month > 12 || day > 31 || year < 0 || month < 1 || day < 1)
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

time_t BitcoinExchange::convert_date_time(int year, int month, int day)
{
    struct tm t;
    std::memset(&t, 0, sizeof(t)); 
    
    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = day;

    return std::mktime(&t);
}

std::string change_to_string(int year, int month, int day)
{
    std::ostringstream oss;

    oss << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

time_t BitcoinExchange::check_date(std::string date)
{


    char str_copy[100];
    strcpy(str_copy, date.c_str());
    const char *fnd = "-";
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
        return ERROR;
    if (year < MIN_YEAR || year > MAX_YEAR)
        return ERROR;
    if (month < MIN_MONTH || month > MAX_MONTH)
        return ERROR;
    if (day < 1 || day > 31)
        return ERROR;
    time_t time = this->convert_date_time(static_cast<int> (year), static_cast<int> (month),
        static_cast<int> (day));
    std::string check_str = unconvert_time(time);
    std::string orig_str = change_to_string(static_cast<int> (year), static_cast<int> (month),
        static_cast<int> (day));
    if (check_str != orig_str)
        return ERROR;
    return (time);
}

int check_full_string(std::string str, int flag)
{

    if (flag == CHECK)
    {
        int count = std::count(str.begin(), str.end(), '-');
        if ( count != 2)
        {
            std::cerr << "Error: bad input => " << str  << std::endl;
            return (ERROR);
        }
    }

    else 
    {

        int count_pipe = std::count(str.begin(), str.end(), PIPE);
        if ( count_pipe != 1)
        {
            std::cerr << "Error: bad input => " << str  << std::endl;
            return (ERROR);
        }

        while(str.find_first_not_of("0123456789-|. \t") != std::string::npos)
        {
            std::cerr << "Error: bad input => " << str  << std::endl;
            return (ERROR);
        }
    }
    return (0);
}

int    check_value_str(std::string value_str)
{
    if (value_str.length() > 15)
    {
        std::cerr << "Error: bad input => " << value_str  << std::endl;
        return (ERROR);
    }
    int dot_count = std::count(value_str.begin(), value_str.end(), '.');
    if (dot_count > 1)
    {
        std::cerr << "Error: bad input => " << value_str  << std::endl;
        return (ERROR);
    }
    int  i = 0;
    while(value_str[i])
    {
        if ((std::isspace(value_str[i])))
        {
            std::cerr << "Error: bad input => " << value_str  << std::endl;
            return (ERROR);
        }
        i++;
    }

    return (0);
}
void BitcoinExchange::read_file_input(std::string file_name)
{
    std::ifstream file_input (file_name.c_str());
    if (!file_input)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    getline(file_input, line);

    while(getline(file_input, line))
    {
        line  = ft_get_line_trim(line);
        if (line.empty())
            continue ;
        if (check_full_string(line, 0) == ERROR)
            continue ;
  
        std::string date = line.substr(0, line.find_first_of("|"));
        if (check_full_string(date, CHECK) == ERROR)
            continue ;
        std::string value_str = line.substr(line.find_first_of("|") + 1, line.size());
        date = ft_get_line_trim(date);
        value_str = ft_get_line_trim(value_str);
        check_value_str(value_str);
        time_t time_data = check_date(date);
        if( time_data == ERROR)
        {
            std::cerr << "Error: bad input date => " << date << std::endl;
            continue ; 
        }

        double  value = std::strtod(value_str.c_str(), nullptr);
        if ( static_cast <long long > (value ) < 0 )
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue ;
        }

        if (static_cast <long long >(value ) > 1000  )
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue ;
        }
        
        std::map<time_t , double>::const_iterator it = this->cont_map.find(time_data);
        if (it != this->cont_map.end())
        {
            double result = value * it->second;
            std::cout << unconvert_time(time_data) << " => " << value << " = " << result << std::endl;
        }
        else
        {
            std::map<time_t , double>::const_iterator lower = this->cont_map.lower_bound(time_data);
            if (lower == this->cont_map.begin())
            {
                std::cerr << "Error: no earlier date available for " << date << std::endl;
                continue ;
            }
            --lower;
            double result = value * lower->second;
            std::cout << unconvert_time(time_data) << " => " << value << " = " << result << std::endl;
        }
    }
}
