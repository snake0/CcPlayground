//
// Created by SNAKE on 9/12/19.
//

#ifndef LEETCODE_BINARYSEARCHTREE_H
#define LEETCODE_BINARYSEARCHTREE_H

#include "include_for_cc.h"

template<class Comparable, class Comparator=less<Comparable>>
class BinarySearchTree {
 public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree &rhs);
  BinarySearchTree(BinarySearchTree &&rhs);
  ~BinarySearchTree();

  const Comparable &findMin() const;
  const Comparable &findMax() const;
  bool contains(const Comparable &x) const;
  bool isEmpty() const;
  void printTree(ostream &out = cout) const;

  void makeEmpty();
  void insert(const Comparable &x);
  void insert(Comparable &&x);
  void remove(const Comparable &x);

  BinarySearchTree &operator=(const BinarySearchTree &rhs);
  BinarySearchTree &operator=(BinarySearchTree &&rhs);

 private:
  struct BinaryNode {
    Comparable element;
    Comparator isLessThan;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
      : element{theElement}, left{lt}, right{rt} {}

    BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
      : element{std::move(theElement)}, left{lt}, right{rt} {}
  };

  BinaryNode *root;

  void insert(const Comparable &theElement, BinaryNode *t);
  void insert(Comparable &&theElement, BinaryNode *t);
  void remove(const Comparable &theElement, BinaryNode *t);
  BinaryNode *findMin(BinaryNode *t) const;
  BinaryNode *findMax(BinaryNode *t) const;
  bool contains(const Comparable &x, const BinaryNode *t) const;
  void makeEmpty(BinaryNode *&t);
  void printTree(BinaryNode *t, ostream &out) const;
  BinaryNode *clone(BinaryNode *t) const;
};


#endif //LEETCODE_BINARYSEARCHTREE_H
