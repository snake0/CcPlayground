//
// Created by SNAKE on 2019-08-27.
//

#ifndef LEETCODE_INCLUDE_H
#define LEETCODE_INCLUDE_H

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <cwchar>
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
#include <vector>


#define DEBUG_LOG true

enum ORDER {
  PRE, IN, POST
};

struct ListNode {
  int val;
  ListNode* next;

  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newListNode(int val, ListNode* l) {
  ListNode* head = new ListNode(val);
  head->next = l;
  return head;
}

void coutListNode(ListNode* l) {
  while (l) {
    std::cout << l->val << "->";
    l = l->next;
  }
  std::cout << "p" << std::endl;
}

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* newTreeNode(int val, TreeNode* left, TreeNode* right) {
  TreeNode* root = new TreeNode(val);
  root->left = left;
  root->right = right;
  return root;
}

#define L newListNode
#define T newTreeNode

std::vector<int> bfs(TreeNode* root) {
  std::queue<std::pair<TreeNode*, int>> s;
  s.push(std::make_pair(root, 0));
  int old_level = ~(1 << 31);
  std::vector<int> res(0);

  TreeNode* top;
  while (!s.empty()) {
    auto back = s.front();
    int cur_level = back.second;
    top = back.first;
    s.pop();

    if (cur_level > old_level && DEBUG_LOG)
      std::cout << std::endl;

    if (top) {
      if (DEBUG_LOG)
        std::cout << top->val << " ";
      res.push_back(top->val);
      s.emplace(std::make_pair(top->left, cur_level + 1));
      s.emplace(std::make_pair(top->right, cur_level + 1));
    } else if (DEBUG_LOG)
      std::cout << "p ";
    old_level = cur_level;
  }
  return res;
}

std::vector<int> dfs(TreeNode* root, ORDER order) {
  assert(order >= PRE && order <= POST);

  std::vector<int> path(0);
  std::stack<std::pair<TreeNode*, bool>> s;
  s.push(std::make_pair(root, false));

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
      auto n = std::make_pair(root, true), l = std::make_pair(root->left, false);
      auto r = std::make_pair(root->right, false);
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

#endif //LEETCODE_INCLUDE_H
