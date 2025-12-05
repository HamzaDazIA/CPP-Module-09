#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>   // for std::setw and std::setfill
#include <cstring>   // for memset

int main()
{
    std::string date = "2005-5-27";

    // 1) Parse
    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    // 2) Fill struct tm
    struct tm t;
    std::memset(&t, 0, sizeof(t));   // IMPORTANT!

    t.tm_year = year - 1900; // FIX: years since 1900
    t.tm_mon  = month - 1;   // 0-11
    t.tm_mday = day;

    // 3) Convert to time_t
    time_t timestamp = std::mktime(&t);

    std::cout << "Converted time_t: " << timestamp << "\n";

    // ------------------------------
    // 4) Convert time_t BACK to date
    // ------------------------------
    struct tm *back = std::localtime(&timestamp);

    int y = back->tm_year + 1900;
    int m = back->tm_mon + 1;
    int d = back->tm_mday;

    // Print in YYYY-MM-DD format
    std::cout << "Converted back: "
              << y << "-"
              << std::setw(2) << std::setfill('0') << m << "-"
              << std::setw(2) << std::setfill('0') << d
              << std::endl;

    return 0;
}
