#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>   // for std::setw and std::setfill
#include <cstring>  

using namespace std;

int main() {
    string str = "geeks,for,geeks";

    // Delimiter
        const char *del = ",";
        char str_copy[100]; // Create a mutable copy of the string
        strcpy(str_copy, str.c_str()); // Copy the original string to the mutable copy

        // Splitting the string based on the
    	// delimiter
        char *t = strtok(str_copy, del);

        // Continue extracting substring till
    	// strtok() does not returns nullptr
        while (t != nullptr) {
                cout << "\"" << t << "\"" << " ";

                // Get the next substring
                t = strtok(nullptr, del);
        }
    return 0;
}