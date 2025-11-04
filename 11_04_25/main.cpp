#include <iostream>
#include <string>
#include <regex>
#include <format>
#include "date.h"

int main()
{
    std::regex dateRegex{R"((\d{4})(\/|-)(1[0-2]|0?[1-9])(\2)([1-2][0-9]|3[0-1]|0?[1-9]))"};
    while (true)
    {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if (!getline(std::cin, str) || str == "q")
        {
            break;
        }
        std::smatch m;
        if (std::regex_match(str, m, dateRegex))
        {
            date myDate(stoi(m[3]), stoi(m[5]), stoi(m[1]));
            m[1];
            m[2];
            m[3];

            std::cout << std::format("  Valid Date: Year={}, month={}, day={}", myDate.getYear(), myDate.getMonth(), myDate.getDay()) << std::endl;
        }
        else
        {
            std::cout << "  Invalid Date!" << std::endl;
        }
    }
    return 0;
}