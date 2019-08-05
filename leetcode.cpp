#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>


using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /*
    // 142
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
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
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr) return res;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> oneLevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode *t = q.front();
                q.pop();

                oneLevel.emplace_back(t->val);
                if (t->left != nullptr) q.push(t->left);
                if (t->right != nullptr) q.push(t->right);
            }

            res.emplace_back(oneLevel);
        }

        return res;
    }

    // 61
    ListNode *rotateRight(ListNode *head, int k) {
        if (!head || !head->next || !k)
            return head;
        vector<ListNode *> list;
        ListNode *h = head;
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
    bool containDuplicates(ListNode *node, ListNode **store) {
        if (!(node && node->next))
            return false;
        int val = node->val;

        ListNode *next = node->next;
        while (next && next->val == val)
            next = next->next;

        if (next == node->next)
            return false;
        if (store)
            *store = next;
        return true;
    }

    ListNode *deleteDuplicates(ListNode *head) {
        if (!head)
            return head;
        ListNode *p;
        ListNode *h = head, *bh = nullptr;
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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int n = lists.size();
        if (n == 0)
            return nullptr;
        merge(lists, 0, n - 1);
        return lists[0];
    }

    void merge(vector<ListNode *> &lists, int left, int right) {
        if (left == right)
            return;
        int mid = (left + right) / 2;
        merge(lists, left, mid);
        merge(lists, mid + 1, right);
        ListNode *mergeList = mergeTwoList(lists[left], lists[mid + 1]);
        lists[left] = mergeList;
    }

    ListNode *mergeTwoList(ListNode *list1, ListNode *list2) {
        if (list1 == nullptr)
            return list2;
        else if (list2 == nullptr)
            return list1;
        ListNode *result;

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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode *t = head, *h = head, *bh = nullptr;
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
    string largestNumber(vector<int> &nums) {
        string res;
        int size = nums.size();

        vector<string> strs = vector<string>(size);
        for (int i = 0; i < size; ++i)
            strs[i] = to_string(nums[i]);

        sort(strs.begin(), strs.end(), [](string a, string b) {
            return a + b > b + a;
        });

        for (int i = 0; i < size; ++i)
            res += strs[i];
        return res[0] == '0' ? "0" : res;
    }

    // 240
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
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
            } else return true;
        }
        return false;
    }
     */

    // 29
    int divide(int dividend, int divisor) {

    }

    // 287
    int findDuplicate(vector<int> &nums) {
        if (nums.size() > 1) {

        }
    }
};

int main() {
    Solution S;
    cout << S.divide(10, 3);
}