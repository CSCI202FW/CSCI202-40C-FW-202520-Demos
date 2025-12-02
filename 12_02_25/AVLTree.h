#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include "linkedStack.h"
#include <sstream>

template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    void insert(const t &insertItem);
    AVLTree(int (*comp)(const t &, const t &));
    // void deleteNode(const t &deleteItem);
    class Iterator
    {
    public:
        Iterator(nodeType<t> *currentNode);
        bool hasNext();
        t next();
        Iterator operator++();
        t &operator*();

    private:
        linkedStack<nodeType<t> *> nodeStack;
        void pushLeftNodes(nodeType<t> *node);
    };
    Iterator begin() { return Iterator(this->getRoot()); };
    Iterator find(const t &searchItem) const;
    Iterator end() { return Iterator(nullptr); };

private:
    void balanceFromLeft(nodeType<t> *&currentNode);
    void balanceFromRight(nodeType<t> *&currentNode);
    void rotateToLeft(nodeType<t> *&currentNode);
    void rotateToRight(nodeType<t> *&currentNode);
    void insertIntoAVL(nodeType<t> *&currentNode, nodeType<t> *newNode, bool &isTaller);
    Iterator find(const t &searchItem, nodeType<t> *currentItem) const;
};

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : binarySearchTree<t>(comp) {}

template <class t>
void AVLTree<t>::insert(const t &insertItem)
{
    bool isTaller = false;
    nodeType<t> *newNode = new nodeType<t>;
    newNode->data = new t(insertItem);
    newNode->bfactor = 0;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    insertIntoAVL(this->getRoot(), newNode, isTaller);
}

template <class t>
void AVLTree<t>::insertIntoAVL(nodeType<t> *&currentNode, nodeType<t> *newNode, bool &isTaller)
{
    if (currentNode == nullptr)
    {
        currentNode = newNode;
        isTaller = true;
    }
    else
    {
        int cmp = this->compare(**newNode, **currentNode);
        if (cmp == 0)
        {
            throw std::invalid_argument("No duplicates allowed");
        }
        else if (cmp == -1)
        {
            insertIntoAVL(currentNode->lLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    balanceFromLeft(currentNode);
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(currentNode->rLink, newNode, isTaller);
            if (isTaller)
            {
                switch (currentNode->bfactor)
                {
                case -1:
                    currentNode->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    currentNode->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(currentNode);
                    isTaller = false;
                }
            }
        }
    }
}

template <class t>
void AVLTree<t>::balanceFromLeft(nodeType<t> *&currentNode)
{
    nodeType<t> *lChild;
    nodeType<t> *lChild_RChild;
    lChild = currentNode->lLink;

    switch (lChild->bfactor)
    {
    case -1: // left subtree of the current node is left high
        currentNode->bfactor = 0;
        lChild->bfactor = 0;
        rotateToRight(currentNode);
        break;
    case 0: // left subtree of current node is balanced is an error
        throw std::runtime_error("Left subtree is balanced.");
    case 1: // left subtree of the current node is right high (current node is left high)
        lChild_RChild = lChild->rLink;
        switch (lChild_RChild->bfactor)
        {
        case -1:
            currentNode->bfactor = 1;
            lChild->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = 0;
            lChild->bfactor = -1;
            break;
        }
        lChild_RChild->bfactor = 0;
        rotateToLeft(currentNode->lLink);
        rotateToRight(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::balanceFromRight(nodeType<t> *&currentNode)
{
    nodeType<t> *rChild = currentNode->rLink;
    switch (rChild->bfactor)
    {
    case -1:
        switch (rChild->lLink->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rChild->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rChild->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rChild->bfactor = 0;
        }
        rChild->lLink->bfactor = 0;
        rotateToRight(currentNode->rLink);
        rotateToLeft(currentNode);
        break;
    case 0:
        throw std::runtime_error("Right Subtree is balanced.");
    case 1:
        currentNode->bfactor = 0;
        rChild->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    }
}

template <class t>
void AVLTree<t>::rotateToLeft(nodeType<t> *&currentNode)
{
    nodeType<t> *newRootNode;
    if (currentNode == nullptr || currentNode->rLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->rLink;
    currentNode->rLink = newRootNode->lLink;
    newRootNode->lLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
void AVLTree<t>::rotateToRight(nodeType<t> *&currentNode)
{
    nodeType<t> *newRootNode;
    if (currentNode == nullptr || currentNode->lLink == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    newRootNode = currentNode->lLink;
    currentNode->lLink = newRootNode->rLink;
    newRootNode->rLink = currentNode;
    currentNode = newRootNode;
}

template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem) const
{
    return find(searchItem, this->getRoot());
}
template <class t>
AVLTree<t>::Iterator AVLTree<t>::find(const t &searchItem, nodeType<t> *currentItem) const
{
    if (currentItem == nullptr)
    {
        return AVLTree<t>::Iterator(nullptr);
    }
    int cmp = this->compare(searchItem, **currentItem);
    if (cmp == 0)
    {
        return AVLTree<t>::Iterator(currentItem);
    }
    else if (cmp == 1)
    {
        return find(searchItem, currentItem->rLink);
    }
    else
    {
        return find(searchItem, currentItem->lLink);
    }
}

template <class t>
AVLTree<t>::Iterator::Iterator(nodeType<t> *currentNode)
{
    pushLeftNodes(currentNode);
}
template <class t>
bool AVLTree<t>::Iterator::hasNext()
{
    return !nodeStack.isEmptyStack();
}
template <class t>
t AVLTree<t>::Iterator::next()
{
    if (nodeStack.isEmptyStack())
    {
        throw std::out_of_range("No more elements");
    }
    nodeType<t> *node = nodeStack.top();
    nodeStack.pop();
    t data = **node;
    if (node->rLink != nullptr)
    {
        pushLeftNodes(node->rLink);
    }
    return data;
}
template <class t>
AVLTree<t>::Iterator AVLTree<t>::Iterator::operator++()
{
    if (nodeStack.isEmptyStack())
    {
        throw std::out_of_range("No more elements");
    }
    nodeType<t> *node = nodeStack.top();
    nodeStack.pop();
    if (node->rLink != nullptr)
    {
        pushLeftNodes(node->rLink);
    }
    return *this;
}
template <class t>
t &AVLTree<t>::Iterator::operator*()
{
    if (nodeStack.isEmptyStack())
    {
        throw std::out_of_range("No more elements");
    }
    nodeType<t> *node = nodeStack.top();
    return **node;
}
template <class t>
void AVLTree<t>::Iterator::pushLeftNodes(nodeType<t> *node)
{
    while (node != nullptr)
    {
        nodeStack.push(node);
        node = node->lLink;
    }
}
#endif