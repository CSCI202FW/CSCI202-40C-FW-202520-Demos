#include "arrayStack.h"
#include "linkedStack.h"
#include <iostream>
#include <string>
#include <cmath>

// m03 lab a which stack to you prefer why?

std::string getBinaryNumber();
int main()
{
    linkedStack<int> myStack(20);
    myStack.push(7);
    myStack.push(12);
    linkedStack<int> yourStack = myStack;
    myStack.push(34);
    yourStack = myStack;

    std::string binary = getBinaryNumber();
    linkedStack<int> digits;
    for (int i = 0; i < binary.size(); i++)
    {
        if (binary[i] != ' ')
        {
            digits.push(binary[i] - '0');
        }
    }
    int position = 0;
    int decimalNum = 0;
    while (!digits.isEmptyStack())
    {
        int digit = digits.pop();
        decimalNum += pow(2, position) * digit;
        position++;
    }
    std::cout << binary << " in decimal is " << decimalNum << std::endl;
    return 0;
}

std::string getBinaryNumber()
{
    std::string binNumber;
    std::cout << "Enter a number in binary: ";
    std::getline(std::cin >> std::ws, binNumber);
    for (int i = 0; i < binNumber.size(); i++)
    {
        if (binNumber[i] != '1' && binNumber[i] != '0' && binNumber[i] != ' ')
        {
            std::cout << "Please enter only 1s and 0s." << std::endl;
            return getBinaryNumber();
        }
    }
    return binNumber;
}
