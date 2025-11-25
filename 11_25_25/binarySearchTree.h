#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
class binarySearchTree : public binaryTreeType<t>
{
public:
    binarySearchTree(int (*comp)(const t &, const t &));
    void insert(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);

private:
    int (*compare)(const t &item1, const t &item2);
    void deleteFromTree(binaryNode<t> *&currentNode);
    bool search(const t &searchItem, binaryNode<t> *currentNode);
    void insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode);
};

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &, const t &))
{
    this->compare = comp;
}

template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
    binaryNode<t> *newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insert(newNode, this->getRoot());
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->getRoot());
}

template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
    binaryNode<t> *current;
    binaryNode<t> *currentParent;
    bool found = false;
    if (this->isEmpty())
    {
        throw std::invalid_argument("Cannot delete from an empty tree");
    }
    current = this->getRoot();
    currentParent = current;
    int cmp;
    while (current != nullptr && !found)
    {
        cmp = compare(deleteItem, *current->data);
        if (cmp == 0)
        {
            found = true;
        }
        else
        {
            currentParent = current;
            if (cmp == -1)
            {
                current = current->lLink;
            }
            else
            {
                current = current->rLink;
            }
        }
    }
    if (!found)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    else
    {
        if (current == this->getRoot())
        {
            deleteFromTree(this->getRoot());
        }
        else if (compare(deleteItem, *currentParent->data) == -1)
        {
            deleteFromTree(currentParent->lLink);
        }
        else
        {
            deleteFromTree(currentParent->rLink);
        }
    }
}

template <class t>
void binarySearchTree<t>::deleteFromTree(binaryNode<t> *&currentNode)
{
    binaryNode<t> *replace;
    binaryNode<t> *replaceParent;
    binaryNode<t> *temp;
    if (currentNode == nullptr)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
    }
    else if (currentNode->lLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->rLink;
        delete temp;
    }
    else if (currentNode->rLink == nullptr)
    {
        temp = currentNode;
        currentNode = temp->lLink;
        delete temp;
    }
    else
    {
        replace = currentNode->lLink;
        replaceParent = nullptr;
        while (replace->rLink != nullptr)
        {
            replaceParent = replace;
            replace = replace->rLink;
        }
        t *tempData;
        tempData = currentNode->data;
        currentNode->data = replace->data;
        replace->data = tempData;
        if (replaceParent == nullptr)
        {
            currentNode->lLink = replace->lLink;
        }
        else
        {
            replaceParent->rLink = replace->lLink;
        }
        delete replace;
        replace = nullptr;
    }
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int cmp = compare(searchItem, *currentNode->data);
    if (cmp == 0)
    {
        return true;
    }
    if (cmp == -1)
    {
        return search(searchItem, currentNode->lLink);
    }
    if (cmp == 1)
    {
        return search(searchItem, currentNode->rLink);
    }
    return false;
}

template <class t>
void binarySearchTree<t>::insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int cmp = compare(*insertItem->data, *currentNode->data);
        if (cmp == 0)
        {
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed.");
        }
        else if (cmp == -1)
        {
            insert(insertItem, currentNode->lLink);
        }
        else if (cmp == 1)
        {
            insert(insertItem, currentNode->rLink);
        }
    }
}

#endif