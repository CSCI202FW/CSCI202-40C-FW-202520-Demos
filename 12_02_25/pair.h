#ifndef PAIR_H
#define PAIR_H

template <class k, class v>
class pair
{
    pair(const pair<k, v> &oth);
    pair(const k &key, const v &value);
    pair(const k &key);
    v &getValue();
    k getKey();
    void setValue(const v &value);
    bool operator>(const pair<k, v> &oth) const;
    bool operator>=(const pair<k, v> &oth) const;
    bool operator<(const pair<k, v> &oth) const;
    bool operator<=(const pair<k, v> &oth) const;
    bool operator==(const pair<k, v> &oth) const;
    bool operator!=(const pair<k, v> &oth) const;
    const pair<k, v> &operator=(const pair<k, v> &oth);
    ~pair();

private:
    void copyPair(const pair<k, v> &oth);
    k *key;
    v *value;
};

#endif