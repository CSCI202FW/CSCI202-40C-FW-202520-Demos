#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// M06 part a lab use an AI of your choice to add delete code to the AVL tree the tree should remain balanced.

int main()
{
    map<int, std::string> hobbits;
    std::ifstream name("names.txt");
    for (int i = 0; !name.eof(); i++)
    {
        std::string in;
        std::getline(name >> std::ws, in);
        hobbits.insert(i, in);
    }
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    std::cout << hobbits[6] << std::endl;
    std::cout << std::setw(40) << std::setfill('-') << "-" << std::endl;
    hobbits[0] = "Tasha Oakbottom";
    std::cout << hobbits[0] << std::endl;
    hobbits[15] = "Brianna Button";
    std::cout
        << std::setw(40) << std::setfill('-') << "-" << std::endl;
    for (auto it = hobbits.begin(); it.hasNext(); ++it)
    {
        pair<int, std::string> p = *it;
        std::cout << p.getValue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\nBegin Delete test:\n\n";

    std::cout << "Notes about the delete debugger:\nType -1 to exit\nType -2 to print map\n";

    while (true)
    {

        std::cout << "\n  *** \n";

        int ind;

        std::cout << "Enter index of node to be deleted:";

        std::cin >> ind;

        if (ind == -1)
        {

            break;
        }

        if (ind == -2)
        {

            for (auto it = hobbits.begin(); it.hasNext(); ++it)

            {

                pair<int, std::string> p = *it;

                std::cout << p.getValue() << std::endl;
            }
        }

        else
        {

            try

            {

                std::cout << "Deleting " << hobbits.at(ind) << "\n";

                std::cout << hobbits.deleteItem(ind)
                          << std::endl;
            }

            catch (const std::out_of_range &e)

            {

                std::cout << e.what() << '\n';
            }
        }
    }
}
/*
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Begin Delete test:

Notes about the delete debugger:
Type -1 to exit
Type -2 to print map

  ***
Enter index of node to be deleted:-2
Tasha Oakbottom
Kalimac Gardner
Dreux Hairyfoot
Wandregisilus Longbottom
Uffo Stumbletoe
Pepin Proudbody
Magneric Gluttonbelly
Fredegar Harfoot
Abbo Gluttonbelly
Clotaire Zaragamba
Brianna Button

  ***
Enter index of node to be deleted:0
Deleting Tasha Oakbottom

  ***
Enter index of node to be deleted:-2
Kalimac Gardner
Dreux Hairyfoot
Wandregisilus Longbottom
Uffo Stumbletoe
Pepin Proudbody
Magneric Gluttonbelly
Fredegar Harfoot
Abbo Gluttonbelly
Clotaire Zaragamba
Brianna Button

  ***
*/
/*
Enter index of node to be deleted:0
Deleting Arnoul Goodbody

  ***
Enter index of node to be deleted:1
Deleting Kalimac Gardner

  ***
Enter index of node to be deleted:2
Deleting Dreux Hairyfoot
Cannot rotate empty node.

  ***
Enter index of node to be deleted:4
Deleting Uffo Stumbletoe

  ***
Enter index of node to be deleted:5
Deleting Wandregisilus Longbottom
Cannot rotate empty node.

  ***
Enter index of node to be deleted:6
Deleting Wandregisilus Longbottom

  ***
Enter index of node to be deleted:7
Deleting Fredegar Harfoot

  ***
Enter index of node to be deleted:8
Deleting Abbo Gluttonbelly

  ***
Enter index of node to be deleted:9
Deleting Clotaire Zaragamba

here we segfaulted and were pointed to line 408: switch(currentNode->lLink->bfactor) as currentNode->lLink does not exist and bfactor also does not exist.
*/