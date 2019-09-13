//
// Created by SNAKE on 9/13/19.
//

#ifndef LEETCODE_HASHTABLE_H
#define LEETCODE_HASHTABLE_H

#include "include_for_cc.h"

template<typename Key>
class Hash {
 public:
  size_t operator()(const Key &k) const;
};

template<>
class Hash<string> {
 public:
  size_t operator()(const string &key) const {
    size_t hashVal = 0;

    for (char ch:key)
      hashVal = 37 * hashVal + ch;

    return hashVal;
  };
};

template<>
class Hash<int> {
 public:
  size_t operator()(const int &k) const;
};

template<typename HashedObject>
class HashTable {
 public:
  explicit HashTable(int size = 101) {

  }

  bool contains(const HashedObject &x) const {
    auto &whichList = theLists[myhash(x)];
    return find(begin(whichList), end(whichList), x) != end(whichList);
  }

  void makeEmpty() {
    for (auto &thisList:theLists)
      thisList.clear();
  }

  bool insert(const HashedObject &x) {
    return false;
  }

  bool insert(HashedObject &&x) {
    auto &whichList = theLists[myhash(x)];
    if (find(begin(whichList), end(whichList), x) != end(whichList))
      return false;
    whichList.push_back(x);

    if (++currentSize > theLists.size())
      rehash();

    return true;
  }

  bool remove(const HashedObject &x) {
    auto &whichList = theLists[myhash(x)];
    auto itr = find(begin(whichList), end(whichList), x);

    if (itr == end(whichList))
      return false;

    whichList.erase(itr);
    --currentSize;
    return true;
  }

 private:
  vector<list<HashedObject>> theLists;
  int currentSize;

  void rehash() {

  }

  size_t myhash(const HashedObject &x) const {
    static Hash<HashedObject> hf;
    return hf(x) % theLists.size();
  }
};

#endif //LEETCODE_HASHTABLE_H
