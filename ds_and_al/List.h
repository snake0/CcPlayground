//
// Created by SNAKE on 2019-09-09.
//

#ifndef LEETCODE_LIST_H
#define LEETCODE_LIST_H

#include "include_for_cc.h"

template<typename Object>
class List {
 private:
  struct Node {
    Object data;
    Node *prev, *next;

    Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
      : data{d}, prev{p}, next{n} {}

    Node(const Object &&d, Node *p = nullptr, Node *n = nullptr)
      : data{std::move(d)}, prev{p}, next{n} {}

  };

 public:
  class const_iterator {
   public:
    const_iterator() : current{nullptr} {}

    const_iterator(Node *p) : current{p} {}

    const Object &operator*() const { return retrieve(); }

    const_iterator &operator++() {
      if (current == theList->tail)
        throw IteratorOutOfBoundException{};
      current = current->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old = *this;
      ++(*this);
      return old;
    }

    const_iterator &operator--() {
      if (current == theList->head->next)
        throw IteratorOutOfBoundException{};
      current = current->prev;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator old = *this;
      --(*this);
      return old;
    }

    const_iterator &operator+(int step) {
      while (step--)
        ++(*this);
      return *this;
    }

    const_iterator &operator-(int step) {
      while (step--)
        --(*this);
      return *this;
    }

    bool operator==(const const_iterator &rhs) { return theList == rhs.theList && current == rhs.current; }

    bool operator!=(const const_iterator &rhs) { return !(*this == rhs); }

   protected:
    const List<Object> *theList;
    Node *current;

    Object &retrieve() const { return current->data; };

    const_iterator(const List<Object> &lst, Node *p)
      : theList{&lst}, current{p} {}

    void assertValid() const {
      if (theList == nullptr || current == nullptr || current == theList->head)
        throw IteratorOutOfBoundException{};
    }

    friend class List;
  };

  class iterator : public const_iterator {
   public:
    iterator() {}

    Object &operator*() { return const_iterator::retrieve(); }

    const Object &operator*() const { return const_iterator::operator*(); }

    iterator &operator++() {
      if (this->current == this->theList->tail)
        throw IteratorOutOfBoundException{};
      this->current = this->current->next;
      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      ++(*this);
      return old;
    }

    iterator &operator--() {
      if (this->current == this->theList->head->next)
        throw IteratorOutOfBoundException{};
      this->current = this->current->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator old = *this;
      --(*this);
      return old;
    }

    iterator operator+(int step) {
      while (step--)
        ++(*this);
      return *this;
    }

    iterator operator-(int step) {
      while (step--)
        --(*this);
      return *this;
    }

   protected:
    iterator(Node *p) : const_iterator{p} {}

   private:
    friend class List;
  };

 public:
  List() { init(); }


  ~List() {
    clear();
    delete head;
    delete tail;
  }

  List(const List &rhs) {
    init();
    for (auto &x:rhs)
      push_back(x);
  }

  List &operator=(const List &rhs) {
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  List(List &&rhs)
    : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.theSize = 0;
  }

  List &operator=(List &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);

    return *this;
  }

  iterator begin() {
    iterator p{head->next};
    p.theList = this;
    return p;
  }

  const_iterator begin() const {
    iterator p{head->next};
    p.theList = this;
    return p;
  }

  iterator end() {
    iterator p{tail};
    p.theList = this;
    return p;
  }

  const_iterator end() const {
    iterator p{tail};
    p->theList = this;
    return p;
  }

  int size() const { return theSize; }

  bool empty() const { return theSize == 0; }

  void clear() {
    while (!empty())
      pop_front();
  }

  Object &front() { return *begin(); }

  const Object &front() const { return *begin(); }

  Object &back() { return *--end(); }

  const Object &back() const { return *--end(); }

  void push_front(const Object &x) { insert(begin(), x); }

  void push_front(Object &&x) { insert(begin(), std::move(x)); }

  void push_back(const Object &x) { insert(end(), x); }

  void push_back(Object &&x) { insert(end(), std::move(x)); }

  void pop_front() { erase(begin()); }

  void pop_back() { erase(--end()); }

  iterator insert(iterator itr, const Object &x) {
    itr.assertValid();
    if (itr.theList != this)
      throw IteratorMisMatchException{};

    Node *p = itr.current;
    ++theSize;
    return {
      p->prev = p->prev->next = new Node{x, p->prev, p}
    };
  }

  iterator insert(iterator itr, Object &&x) {
    itr.assertValid();
    if (itr.theList != this)
      throw IteratorMisMatchException{};

    ++theSize;
    Node *p = itr.current;
    return {
      p->prev = p->prev->next = new Node{std::move(x), p->prev, p}
    };
  }

  iterator erase(iterator itr) {
    Node *p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;

    return retVal;
  }

  iterator erase(iterator from, iterator to) {
    for (iterator itr = from; itr != to;)
      itr = erase(itr);

    return to;
  }

  void print(ostream &out = cout) {
    Node *iter = head->next;
    while (iter != tail) {
      out << iter->data << " -> ";
      iter = iter->next;
    }
    out << "ph\n";
  }

 private:
  int theSize;
  Node *head, *tail;

  void init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
  }

};


#endif //LEETCODE_LIST_H
