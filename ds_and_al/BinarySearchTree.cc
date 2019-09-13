//
// Created by SNAKE on 9/12/19.
//

#include "BinarySearchTree.h"

template<class Comparable, class Comparator>
using BinaryNode = typename BinarySearchTree<Comparable, Comparator>::BinaryNode;

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator>::BinarySearchTree() {

}

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator>::
BinarySearchTree(const BinarySearchTree &rhs) {

}

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator>::BinarySearchTree(BinarySearchTree &&rhs) {

}

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator>::~BinarySearchTree() {

}

template<class Comparable, class Comparator>
const Comparable &BinarySearchTree<Comparable, Comparator>::findMin() const {
  return findMin(root)->element;
}

template<class Comparable, class Comparator>
const Comparable &BinarySearchTree<Comparable, Comparator>::findMax() const {
  return findMax(root)->element;
}

template<class Comparable, class Comparator>
bool BinarySearchTree<Comparable, Comparator>::contains(const Comparable &x) const {
  return contains(x, root);
}

template<class Comparable, class Comparator>
bool BinarySearchTree<Comparable, Comparator>::isEmpty() const {
  return root == nullptr;
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::printTree(ostream &out) const {

}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::makeEmpty() {

}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::insert(const Comparable &x) {
  insert(x, root);
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::insert(Comparable &&x) {
  insert(x, root);
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::remove(const Comparable &x) {
  remove(x, root);
}

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator>
&BinarySearchTree<Comparable, Comparator>::operator=(const BinarySearchTree &rhs) {
  return BinarySearchTree();
}

template<class Comparable, class Comparator>
BinarySearchTree<Comparable, Comparator> &
BinarySearchTree<Comparable, Comparator>::operator=(BinarySearchTree &&rhs) {
  return BinarySearchTree();
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::insert(
  const Comparable &theElement, BinarySearchTree::BinaryNode *t) {
  if (t == nullptr)
    t = new BinaryNode{theElement, nullptr, nullptr};
  else if (theElement < t->element)
    insert(theElement, t->left);
  else if (theElement > t->element)
    insert(theElement, t->right);
  else;
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::insert(
  Comparable &&theElement, BinarySearchTree::BinaryNode *t) {
  if (t == nullptr)
    t = new BinaryNode{std::move(theElement), nullptr, nullptr};
  else if (theElement < t->element)
    insert(std::move(theElement), t->left);
  else if (theElement > t->element)
    insert(std::move(theElement), t->right);
  else;
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::remove(
  const Comparable &theElement, BinarySearchTree::BinaryNode *t) {

}

template<class Comparable, class Comparator>
BinaryNode<Comparable, Comparator> *
BinarySearchTree<Comparable, Comparator>::
findMin(BinarySearchTree::BinaryNode *t) const {
  if (t != nullptr)
    for (; t->left; t = t->left);
  return t;
}

template<class Comparable, class Comparator>
BinaryNode<Comparable, Comparator> *
BinarySearchTree<Comparable, Comparator>::
findMax(BinarySearchTree::BinaryNode *t) const {
  if (t != nullptr)
    for (; t->left; t = t->left);
  return t;
}

template<class Comparable, class Comparator>
bool BinarySearchTree<Comparable, Comparator>::contains(
  const Comparable &x, const BinarySearchTree::BinaryNode *t) const {
  if (t != nullptr)
    for (; t->right; t = t->right);
  return t;
}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::
makeEmpty(BinarySearchTree::BinaryNode *&t) {

}

template<class Comparable, class Comparator>
void BinarySearchTree<Comparable, Comparator>::printTree(
  BinarySearchTree::BinaryNode *t, ostream &out) const {

}

template<class Comparable, class Comparator>
BinaryNode<Comparable, Comparator>
*BinarySearchTree<Comparable, Comparator>::
clone(BinarySearchTree::BinaryNode *t) const {
  return nullptr;
}