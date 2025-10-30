#include <iostream>
#include <limits>
#include "donut.h"

void resetStream();
void codeGradeLoopFix(std::string errLocation);
std::string getIcing();
std::string getTopping(std::string);
std::string getDrizzle();
void icingPrompt();
void drizzlePrompt();
void toppingPrompt(std::string);

int main()
{
    Donut *d = nullptr;
    int numDonuts;
    std::string icing = getIcing();
    std::string topping = getTopping(icing);
    std::string drizzle = getDrizzle();
    d = new Donut(icing, topping, drizzle);
    std::cout << *d << std::endl;
    /*   (*d).BACON;
       d->BACON;
    */
    Donut **donutlist = nullptr;
    std::cout << "how many donuts? " << std::endl;
    std::cin >> numDonuts;
    while (!std::cin || numDonuts < 1)
    {
        codeGradeLoopFix("Number of Donuts");
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << "You entered an invalid number of donuts. " << std::endl;
        std::cout << "how many donuts? " << std::endl;
        std::cin >> numDonuts;
    }
    donutlist = new Donut *[numDonuts];
    for (int i = 0; i < numDonuts; i++)
    {
        std::cout << i + 1 << " Donut of " << numDonuts << std::endl;
        icing = getIcing();
        topping = getTopping(icing);
        drizzle = getDrizzle();
        try
        {
            donutlist[i] = new Donut(icing, topping, drizzle);
            std::cout << *donutlist[i] << std::endl;
        }
        catch (std::invalid_argument e)
        {
            std::cerr << e.what() << '\n';
            i--;
        }
        std::cout << "Your order:" << std::endl;
    }
    for (int i = 0; i < numDonuts; i++)
    {
        std::cout << *donutlist[i] << std::endl;
        delete donutlist[i];
    }
    delete d;
    delete[] donutlist;

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation);
    }
}

std::string getIcing()
{
    std::string ice;
    icingPrompt();
    std::cin >> std::ws;
    std::getline(std::cin, ice);
    std::string icingLower = ice;
    std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    while (!Donut::strToIce.count(icingLower))
    {
        codeGradeLoopFix("main.cpp::getIcing()");
        // resetStream();
        std::cout << ice << " is not a valid choice. " << std::endl;
        icingPrompt();
        std::cin >> std::ws;
        std::getline(std::cin, ice);
        icingLower = ice;
        std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    }
    return ice;
}

std::string getTopping(std::string icing)
{
    std::string top;
    std::transform(icing.begin(), icing.end(), icing.begin(), ::tolower);
    toppingPrompt(icing);
    std::cin >> std::ws;
    std::getline(std::cin, top);
    std::string topCopy = top;
    std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
    if (icing == "none")
    {
        while (topCopy != "cinnamon sugar" && topCopy != "powdered sugar" && topCopy != "none")
        {
            codeGradeLoopFix("main.cpp::getTopping(\"none\")");
            std::cout << top << "is not valid for icing " << icing << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    else
    {
        while (!Donut::strToTop.count(topCopy))
        {
            codeGradeLoopFix("main.cpp::getTopping()");
            std::cout << top << " is not a valid topping." << std::endl;
            toppingPrompt(icing);
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    return top;
}

void icingPrompt()
{
    std::cout << "Choose your icing from the choices below: " << std::endl;
    for (std::map<Donut::icingType, std::string>::const_iterator it = Donut::iceToStr.begin(); it != Donut::iceToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

std::string getDrizzle()
{
    std::string drizzle;
    drizzlePrompt();
    std::cin >> std::ws;
    std::getline(std::cin, drizzle);
    std::string drizzleLower = drizzle;
    std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    while (!Donut::strToDrizzle.count(drizzleLower))
    {
        codeGradeLoopFix("main.cpp::getDrizzle()");
        std::cout << drizzle << " is not a valid drizzle choice." << std::endl;
        drizzlePrompt();
        std::cin >> std::ws;
        std::getline(std::cin, drizzle);
        drizzleLower = drizzle;
        std::transform(drizzleLower.begin(), drizzleLower.end(), drizzleLower.begin(), ::tolower);
    }
    return drizzle;
}

void drizzlePrompt()
{
    std::cout << "Choose your drizzle from the choices below:" << std::endl;
    for (std::map<Donut::drizzleType, std::string>::const_iterator it = Donut::drizzleToStr.begin(); it != Donut::drizzleToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
}

void toppingPrompt(std::string icing)
{
    std::cout << "Choose your topping from the choices below:" << std::endl;
    if (icing == "none")
    {
        std::cout << "Cinnamon Sugar" << std::endl;
        std::cout << "Powdered Sugar" << std::endl;
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto it = Donut::topToStr.begin(); it != Donut::topToStr.end(); ++it)
        {
            std::cout << it->second << std::endl;
        }
    }
}
