#include <iostream>
#include <chrono>
#include <ctime> // For std::ctime

int main() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert to a time_t for printing with std::ctime
    std::time_t current_time_t = std::chrono::system_clock::to_time_t(now);

    // Print the full date and time string
    std::cout << "Current date and time: " << std::ctime(&current_time_t);

    // To get specific components like hour, minute, second (using C-style struct tm)
    struct tm *local_time = std::localtime(&current_time_t);

    std::cout << "Time of day: " 
              << local_time->tm_hour << ":" 
              << local_time->tm_min << ":" 
              << local_time->tm_sec << std::endl;

    return 0;
}


#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {{1, "Geeks"},
             {2, "For"}, {3, "Geeks"}};

    // Finding element with key 2
    auto it = m.find(2);
    
    if (it != m.end())
        cout << it->first << " " << it->second;
    else cout << "Key not Found!";
    return 0;
}


#include <iostream>
#include <string>
#include <algorithm> // Required for std::count

int main() {
    std::string text = "programming ||| is fun";
    char target_char = '|';

    // Count occurrences of 'g'
    int count = std::count(text.begin(), text.end(), target_char);

    std::cout << "The character '" << target_char << "' appears " << count << " times." << std::endl;

    return 0;
}