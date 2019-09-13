//
// Created by SNAKE on 2019-08-27.
//

#ifndef LEETCODE_INCLUDE_FOR_CC_H
#define LEETCODE_INCLUDE_FOR_CC_H

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <cwchar>
#include <exception>
#include <functional>
#include <fstream>
#include <future>
#include <iostream>
#include <list>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
#define DEBUG_LOG true

enum ORDER {
  PRE, IN, POST
};

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x) : val(x), next(nullptr) {}

  ListNode *newListNode(int v, ListNode *l) {
    ListNode *head = new ListNode(v);
    head->next = l;
    return head;
  }

  void coutListNode(ListNode *l) {
    for (ListNode *h = l; h; h = h->next)
      cout << l->val << "->";
    cout << "p" << endl;
  }
};


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  TreeNode *newTreeNode(int v, TreeNode *l, TreeNode *r) {
    TreeNode *root = new TreeNode(v);
    root->left = l;
    root->right = r;
    return root;
  }

  vector<int> bfs(TreeNode *root) {
    queue<pair<TreeNode *, int>> s;
    s.push(make_pair(root, 0));
    int old_level = ~(1 << 31);
    vector<int> res(0);

    TreeNode *top;
    while (!s.empty()) {
      auto back = s.front();
      int cur_level = back.second;
      top = back.first;
      s.pop();

      if (cur_level > old_level && DEBUG_LOG)
        cout << endl;

      if (top) {
        if (DEBUG_LOG)
          cout << top->val << " ";
        res.push_back(top->val);
        s.emplace(make_pair(top->left, cur_level + 1));
        s.emplace(make_pair(top->right, cur_level + 1));
      } else if (DEBUG_LOG)
        cout << "p ";
      old_level = cur_level;
    }
    return res;
  }

  vector<int> dfs(TreeNode *root, ORDER order) {
    assert(order >= PRE && order <= POST);

    vector<int> path(0);
    stack<pair<TreeNode *, bool>> s;
    s.push(make_pair(root, false));

    bool visited;
    while (!s.empty()) {
      root = s.top().first;
      visited = s.top().second;
      s.pop();
      if (root == nullptr)
        continue;
      if (visited) {
        path.push_back(root->val);
      } else {
        auto n = make_pair(root, true), l = make_pair(root->left, false);
        auto r = make_pair(root->right, false);
        switch (order) {
          case PRE:
            s.push(r);
            s.push(l);
            s.push(n);
            break;
          case IN:
            s.push(r);
            s.push(n);
            s.push(l);
            break;
          case POST:
            s.push(n);
            s.push(r);
            s.push(l);
            break;
        }
      }
    }
    return path;
  }
};


struct IteratorOutOfBoundException : public exception {
  const char *what() const noexcept {
    return "Iterator out of bound exception";
  }
};
struct IteratorMisMatchException : public exception {
  const char *what() const noexcept {
    return "Iterator mismatch bound exception";
  }
};
struct UnderflowException : public exception {
  const char *what() const noexcept {
    return "Underflow exception";
  }
};

#define L newListNode
#define T newTreeNode

#endif //LEETCODE_INCLUDE_FOR_CC_H
