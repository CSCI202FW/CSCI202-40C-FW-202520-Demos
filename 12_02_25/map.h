#ifndef MAP_H
#define MAP_H
#include "pair.h"
#include "AVLTree.h"
template <class k, class v>
class map
{
public:
    map();
    void insert(const k &, const v &);
    v at(const k &) const;
    v &operator[](const k &);
    typename AVLTree<pair<k, v>>::Iterator begin() { return tree.begin(); };
    bool deleteItem(const k &key);

protected:
    static int compare(const pair<k, v> &item1, const pair<k, v> &item2);
    AVLTree<pair<k, v>> tree;
};

template <class k, class v>
map<k, v>::map() : tree(AVLTree<pair<k, v>>(compare))
{
}

template <class k, class v>
void map<k, v>::insert(const k &key, const v &value)
{
    pair<k, v> p(key, value);
    tree.insert(p);
}

template <class k, class v>
v map<k, v>::at(const k &key) const
{
    pair<k, v> p2(key);
    typename AVLTree<pair<k, v>>::Iterator p = tree.find(p2);
    if (p.hasNext())
    {
        return (*p).getValue();
    }
    else
        throw std::out_of_range("The item is not in the map.");
}

template <class k, class v>
v &map<k, v>::operator[](const k &key)
{
    pair<k, v> p2(key);
    typename AVLTree<pair<k, v>>::Iterator p = tree.find(p2);
    if (!p.hasNext())
    {
        v value;
        pair<k, v> p3(key, value);
        tree.insert(p3);
        p = tree.find(p3);
    }
    pair<k, v> *returnP = &*p;
    return returnP->getValue();
}

template <class k, class v>
int map<k, v>::compare(const pair<k, v> &item1, const pair<k, v> &item2)
{
    if (item1 < item2)
    {
        return -1;
    }
    else if (item1 == item2)
    {
        return 0;
    }
    else if (item1 > item2)
    {
        return 1;
    }
    return 1;
}
template <class k, class v>

bool map<k, v>::deleteItem(const k &key)
{

    v value = at(key);

    pair<k, v> deathrowItem(key, value);

    tree.deleteNode(deathrowItem);
    return tree.isBalanced();
}

#endif