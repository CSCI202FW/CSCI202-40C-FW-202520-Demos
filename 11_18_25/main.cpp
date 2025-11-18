#include <iostream>
#include <string>
#include <limits>

const int DEFAULT = 0;
void resetStream();
int factorial(int n);

int main()
{
    factorial(5);
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int factorial(int n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}
