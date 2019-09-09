#include "include_for_cc.h"

class Solution {
 public:
  // 142
  ListNode* detectCycle(ListNode* head) {
    ListNode* fast = head, * slow = head;
    bool flag = false;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        flag = true;
        break;
      }
    }
    if (flag) {
      slow = head;
      while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
      }
      return slow;
    } else return nullptr;
  }

  // 102
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> res;
    if (root == nullptr)
      return res;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      std::vector<int> oneLevel;
      for (int i = q.size(); i > 0; --i) {
        TreeNode* t = q.front();
        q.pop();

        oneLevel.emplace_back(t->val);
        if (t->left != nullptr)
          q.push(t->left);
        if (t->right != nullptr)
          q.push(t->right);
      }

      res.emplace_back(oneLevel);
    }

    return res;
  }

  // 61
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || !k)
      return head;
    std::vector<ListNode*> list;
    ListNode* h = head;
    for (; h; h = h->next)
      list.push_back(h);

    int size = list.size(), start = k % size;
    if (start == 0)
      return head;
    list[size - 1]->next = head;
    list[size - 1 - start]->next = nullptr;
    return list[size - start];
  }

  // 82
  bool containDuplicates(ListNode* node, ListNode** store) {
    if (!(node && node->next))
      return false;
    int val = node->val;

    ListNode* next = node->next;
    while (next && next->val == val)
      next = next->next;

    if (next == node->next)
      return false;
    if (store)
      *store = next;
    return true;
  }

  ListNode* deleteDuplicates(ListNode* head) {
    if (!head)
      return head;
    ListNode* p;
    ListNode* h = head, * bh = nullptr;
    while (h) {
      if (containDuplicates(h, &p)) {
        if (bh)
          bh->next = p;
        else
          head = p;
        h = p;
        continue;
      }
      bh = h;
      h = h->next;
    }
    return head;
  }

  // 23
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    int n = lists.size();
    if (n == 0)
      return nullptr;
    merge(lists, 0, n - 1);
    return lists[0];
  }

  void merge(std::vector<ListNode*>& lists, int left, int right) {
    if (left == right)
      return;
    int mid = (left + right) / 2;
    merge(lists, left, mid);
    merge(lists, mid + 1, right);
    ListNode* mergeList = mergeTwoList(lists[left], lists[mid + 1]);
    lists[left] = mergeList;
  }

  ListNode* mergeTwoList(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr)
      return list2;
    else if (list2 == nullptr)
      return list1;
    ListNode* result;

    if (list1->val <= list2->val) {
      result = list1;
      result->next = mergeTwoList(list1->next, list2);
    } else {
      result = list2;
      result->next = mergeTwoList(list2->next, list1);
    }

    return result;
  }

  // 19
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* t = head, * h = head, * bh = nullptr;
    int gap = n - 1;
    for (int i = 0; i < gap; ++i) {
      t = t->next;
    }
    while (t->next) {
      t = t->next;
      bh = h;
      h = h->next;
    }
    if (t == head)
      return nullptr;
    else if (bh == nullptr)
      return head->next;
    else {
      bh->next = h->next;
      return head;
    }
  }

  // 179
  std::string largestNumber(std::vector<int>& nums) {
    std::string res;
    int size = nums.size();

    std::vector<std::string> strs = std::vector<std::string>(size);
    for (int i = 0; i < size; ++i)
      strs[i] = std::to_string(nums[i]);

    sort(strs.begin(), strs.end(),
         [](std::string a, std::string b) { return a + b > b + a; });

    for (int i = 0; i < size; ++i)
      res += strs[i];
    return res[0] == '0' ? "0" : res;
  }

  // 240
  bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty())
      return false;

    int row = matrix.size() - 1, col = matrix[0].size() - 1;
    int i = row, j = 0;
    while (i >= 0 && j <= col) {
      int t = matrix[i][j];
      if (t > target) {
        --i;
      } else if (t < target) {
        ++j;
      } else
        return true;
    }
    return false;
  }

  // 29
  int divide(int dividend, int divisor) {
    auto m = (long long) dividend, n = (long long) divisor;

    bool a = true, b = true;
    if (dividend < 0) {
      m = -m;
      a = false;
    }
    if (divisor < 0) {
      n = -n;
      b = false;
    }

    long long ns, p, res = 0;
    while (m >= n) {
      ns = n;
      p = 1;
      while (ns <= m) {
        p <<= 1;
        ns <<= 1;
      }
      res += p >> 1;
      m -= ns >> 1;
    }
    res = a ^ b ? -res : res;
    return res > INT_MAX ? INT_MAX : (int) res;
  }

  // 287
  int findDuplicate(std::vector<int>& nums) {
    if (nums.size() > 1) {
      int slow = nums[0], fast = nums[nums[0]];
      while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
      }
      fast = 0;
      while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
      }
      return slow;
    }
    return -1;
  }

  // 3
  int lengthOfLongestSubstring(std::string s) { return 1; }

  // 144
  std::vector<int> preorderTraversal(TreeNode* root) {
    std::vector<int> ret = std::vector<int>();
    return ret;
  }

  // ?
  std::vector<std::vector<int>> generate(int numRows) {
    std::vector<std::vector<int>> ans(numRows);
    if (numRows == 0)
      return ans;

    ans[0] = std::vector<int>{1};
    if (numRows > 1) {
      for (int i = 0; i < numRows - 1; ++i) {
        std::vector<int> tmp(i + 2);
        tmp[0] = 1;
        tmp[i + 1] = 1;
        for (int j = 1; j < ans[i].size(); ++j) {
          tmp[j] = ans[i][j] + ans[i][j - 1];
        }
        ans[i + 1] = tmp;
      }
    }
    return ans;
  }

  std::vector<int> getRow(int rowIndex) {
    std::vector<int> res(rowIndex, 1), tmp = res;
    for (int i = 1; i < rowIndex; ++i) {
      for (int j = 1; j < i; ++j) {
        tmp[j] = res[j - 1] + res[j];
      }
      res = tmp;
    }
    return res;
  }

  ListNode* reverseList(ListNode* head) {
    if (!(head && head->next))
      return head;
    ListNode* h = head, * bh = nullptr;
    while (h) {
      ListNode* ah = h->next;
      h->next = bh;
      bh = h;
      h = ah;
    }
    return bh;
  }

  ListNode* reverseListRecursive(ListNode* head) {
    if (!(head && head->next))
      return head;
    ListNode* l = reverseListRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return l;
  }

  // 14
  std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty())
      return "";
    std::string ret = strs[0];
    return ret;
  }

  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1 || (l2 && l1->val > l2->val))
      std::swap(l1, l2);
    if (l1)
      l1->next = mergeTwoLists(l1->next, l2);
    return l1;
  }

  // 33
  int search(vector<int>& nums, int target) {

  }
};

int main() {
  Solution s;
  vector<int> v = {1, 2, 3, 4};
  s.search(v, 2);
  cout << "hello world";
}