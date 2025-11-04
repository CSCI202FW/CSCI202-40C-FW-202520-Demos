#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("random3.txt"); // open file
    std::vector<std::string> email;
    std::vector<std::string> ivyemail;
    std::vector<std::string> ipaddr;
    std::vector<std::string> phone;
    std::vector<std::string> indphone;
    std::vector<std::string> course;
    std::vector<std::string> date;
    std::vector<std::string> time;
    std::vector<std::string> money;
    std::regex ip{R"(\b(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))"};
    std::regex dollar{R"(\$(?:\d{1,3},(?:\d{3},)*\d{3}|\d+)(?:\.\d{2})*)"};
    while (!in.eof() && in.is_open())
    {
        std::string str;
        getline(in, str);
        const std::sregex_token_iterator end;

        /*ip address*/
        for (std::sregex_token_iterator iter{cbegin(str), cend(str), ip}; iter != end; ++iter)
        {
            ipaddr.push_back(iter->str());
        }
        for (std::sregex_token_iterator iter{cbegin(str), cend(str), dollar}; iter != end; ++iter)
        {
            money.push_back(iter->str());
        }
    }
    return 0;
}