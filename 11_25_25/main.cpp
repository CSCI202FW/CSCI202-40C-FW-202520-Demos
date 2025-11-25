#include "binarySearchTree.h"
#include <iostream>
#include <random>

int compareNumbers(const int &first, const int &second);
// M05 part a lab seed the random number generator (search for seed c++ 11 random numbers)
// run the program 3 times, and use the preorder traversal to draw the shape of the binary tree
int main()
{
    binarySearchTree<int> tree(compareNumbers);
    std::uniform_int_distribution<int> distribution(5, 100);
    std::default_random_engine generator;
    int num = distribution(generator);

    for (int i = 0; i < num; i++)
    {

        try
        {

            tree.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << tree.inorderTraversal() << std::endl;
    std::cout << tree.preorderTraversal() << std::endl;
    std::cout << tree.postorderTraversal() << std::endl;
    std::cout << "Generated num: " << num << std::endl;
    std::cout << "Tree Height: " << tree.treeHeight() << std::endl;
    std::cout << "Tree Nodes: " << tree.treeNodeCount() << std::endl;
    std::cout << "Tree Leaves: " << tree.treeLeavesCount() << std::endl;

    return 0;
}

int compareNumbers(const int &first, const int &second)
{
    if (first < second)
        return -1;
    else if (first == second)
        return 0;
    else
        return 1;
}