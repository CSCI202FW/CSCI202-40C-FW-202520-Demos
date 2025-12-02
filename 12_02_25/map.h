#ifndef MAP_H
#define MAP_H
#include "pair.h"
#include "AVLTree.h"
template <class k, class v>
class map
{
    map();
    void insert(const k &, const v &);
    v at(const k &) const;
    v &operator[](const k &);
    typename AVLTree<pair<k, v>>::Iterator begin() { return tree.begin(); };

protected:
    static int compare(const pair<k, v> &item1, const pair<k, v> &item2);
    AVLTree<pair<k, v>> tree;
};
#endif