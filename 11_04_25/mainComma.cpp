#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <set>
#include <fstream>

int main()
{
    std::regex commaStr{R"((?:\w+ *)+(?=,|$))"};
    std::ifstream in("data.txt");
    while (!in.eof() && in.is_open())
    {
        std::string line;
        std::getline(in, line);
        const std::sregex_iterator end;
        for (std::sregex_iterator iter{std::cbegin(line), std::cend(line), commaStr}; iter != end; ++iter)
        {
            std::cout << (*iter)[0].str() << std::endl;
        }
    }
    return 0;
}