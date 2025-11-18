#include <iostream>
#include <string>
#include <limits>
#include "linkedStack.h"

const int DEFAULT = 0;
void resetStream();
int factorial(int n);
int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower = DEFAULT, int upper = DEFAULT);

bool intInRange(int n, int lower, int upper);
bool intGTX(int n, int x, int = DEFAULT);
bool intLTX(int n, int x, int = DEFAULT);
bool intGTEQ(int n, int x, int = DEFAULT);
bool intLTEQ(int n, int x, int = DEFAULT);
long fibNum(long f[], long n);
void moveDisks(int, char source, char destination, char spare);
void moveDisks(linkedStack<int> &source, linkedStack<int> &destination, linkedStack<int> &spare, char s, char d, char sp);
// M04 part A lab
// use the fibonacci number code from page 296 of the textbook
// implement as a function
// compare with recursive version
// which do you prefer and why?
// submit your preference and the function

int main()
{
    std::string prompt = "Enter a number greater than 0: ";
    std::string err = "Please enter a number greater than 0.";
    int x = inputInt(prompt, err, intGTX, 0);
    std::cout << "Factorial of " << x << " is " << factorial(x) << std::endl;
    prompt = "Enter the first fibonacci number: ";
    err = "The number entered must be greater than 0.";
    long fibNum1 = inputInt(prompt, err, intGTX);
    prompt = "Enter the second fibonacci number: ";
    err = "The number entered must be greater than or equal to " + std::to_string(fibNum1);
    long fibNum2 = inputInt(prompt, err, intGTEQ, fibNum1);
    prompt = "Enter the position of the desired fibonacci number: ";
    err = "The number entered must be greater than 0.";
    long nthFibonacci = inputInt(prompt, err, intGTX);
    long *fibSeq = new long[nthFibonacci];
    for (int i = 0; i < nthFibonacci; i++)
    {
        fibSeq[i] = -1;
    }
    fibSeq[0] = fibNum1;
    fibSeq[1] = fibNum2;
    std::cout << "The " << nthFibonacci << "th Fibonacci number is " << fibNum(fibSeq, nthFibonacci) << std::endl;

    linkedStack<int> source;
    linkedStack<int> destination;
    linkedStack<int> spare;
    for (int i = 4; i > 0; i--)
    {
        source.push(i);
    }
    moveDisks(4, '1', '3', '2');
    std::cout << std::endl
              << std::endl;
    moveDisks(source, destination, spare, '1', '3', '2');

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

int inputInt(std::string &prompt, std::string &err, bool (*valid)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;
    std::cout << std::endl;
    if (std::cin && valid(theNum, lower, upper))
    {
        return theNum;
    }
    if (!std::cin)
    {
        std::cout << "You entered something that is not a number!" << std::endl;
        resetStream();
    }
    std::cout << err << std::endl;
    return inputInt(prompt, err, valid, lower, upper);
}

bool intInRange(int n, int lower, int upper)
{
    return n >= lower && n <= upper;
}

bool intGTX(int n, int x, int)
{
    return n > x;
}

bool intLTX(int n, int x, int)
{
    return n < x;
}

bool intGTEQ(int n, int x, int)
{
    return n >= x;
}

bool intLTEQ(int n, int x, int)
{
    return n <= x;
}

long fibNum(long f[], long n)
{
    if (n < 0)
    {
        return 0;
    }
    if (f[n - 1] != -1)
    {
        return f[n - 1];
    }
    f[n - 1] = fibNum(f, n - 1) + fibNum(f, n - 2);
    return f[n - 1];
}

void moveDisks(int count, char source, char destination, char spare)
{
    if (count > 0)
    {
        moveDisks(count - 1, source, spare, destination);
        std::cout << "Move disk " << count << " from " << source << " to " << destination << std::endl;
        moveDisks(count - 1, spare, destination, source);
    }
}

void moveDisks(linkedStack<int> &source, linkedStack<int> &destination, linkedStack<int> &spare, char s, char d, char sp)
{
    if (!source.isEmptyStack())
    {
        if (!spare.isEmptyStack() && source.peek() > spare.peek())
        {
            moveDisks(spare, source, destination, sp, s, d);
        }
        else
        {

            int num = source.pop();
            spare.push(num);

            std::cout << "Move disk " << num << " from " << s << " to " << sp << std::endl;

            moveDisks(source, spare, destination, s, sp, d);
            moveDisks(destination, spare, source, d, sp, s);
        }
    }
}
