#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cwchar>
#include <functional>
#include <iostream>
#include <list>
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

// #define PRINT

// using namespace std;
using namespace std;

template<typename collection>
void IterPrint(collection c) {
    auto b = c.begin(), e = c.end();
    while (b != e)
        cout << *b++ << " ";
    cout << endl;
}

enum ORDER {
    PRE,
    IN,
    POST
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x)
            : val(x), next(nullptr) {
    }
};

ListNode *newListNode(int val, ListNode *l) {
    ListNode *head = new ListNode(val);
    head->next = l;
    return head;
}

void deleteListNode(ListNode *l) {
    ListNode *ptr = l, *tmp;
    while (ptr) {
        tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
}

void coutListNode(ListNode *l) {
    while (l) {
        cout << l->val << "->";
        l = l->next;
    }
    cout << "phi" << endl;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
            : val(x), left(nullptr), right(nullptr) {
    }
};

TreeNode *newTreeNode(int val, TreeNode *left, TreeNode *right) {
    TreeNode *root = new TreeNode(val);
    root->left = left;
    root->right = right;
    return root;
}

#define L newListNode
#define T newTreeNode

/*
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

#ifdef PRINT
        if (cur_level > old_level)
            cout << endl;
#endif

        if (top) {
#ifdef PRINT
            cout << top->val << " ";
#endif
            res.push_back(top->val);
            s.emplace(make_pair(top->left, cur_level + 1));
            s.emplace(make_pair(top->right, cur_level + 1));
        }
#ifdef PRINT
        else
            cout << "ph ";
#endif
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
*/
class Solution {
public:
    // 142
    /*
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
        } else
            return nullptr;
    }

    // 102
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (root == nullptr)
            return res;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> oneLevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode *t = q.front();
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

        sort(strs.begin(), strs.end(),
             [](string a, string b) { return a + b > b + a; });

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
    int findDuplicate(vector<int> &nums) {
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
    int lengthOfLongestSubstring(string s) { return 1; }

    // 144
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ret = vector<int>();
        return ret;
    }

    // ?
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans(numRows);
        if (numRows == 0)
            return ans;

        ans[0] = vector<int>{1};
        if (numRows > 1) {
            for (int i = 0; i < numRows - 1; ++i) {
                vector<int> tmp(i + 2);
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

    vector<int> getRow(int rowIndex) {
        vector<int> res(rowIndex, 1), tmp = res;
        for (int i = 1; i < rowIndex; ++i) {
            for (int j = 1; j < i; ++j) {
                tmp[j] = res[j - 1] + res[j];
            }
            res = tmp;
        }
        return res;
    }

    ListNode *reverseList(ListNode *head) {
        if (!(head && head->next))
            return head;
        ListNode *h = head, *bh = nullptr;
        while (h) {
            ListNode *ah = h->next;
            h->next = bh;
            bh = h;
            h = ah;
        }
        return bh;
    }

    ListNode *reverseListRecursive(ListNode *head) {
        if (!(head && head->next))
            return head;
        ListNode *l = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = nullptr;
        return l;
    }
     */
    // 14
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty())
            return "";
        string ret = strs[0];
        return ret;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (!l1 || (l2 && l1->val > l2->val))
            swap(l1, l2);
        if (l1)
            l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    }
};

template<typename T>
T GetMax(T a, T b) {
    T result;
    result = (a > b) ? a : b;
    return (result);
}

template<>
string GetMax<string>(string a, string b) {
    if (a + b > b + a)
        return b;
    return a;
};

void process_value(int &i) {
    std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int &&i) {
    std::cout << "RValue processed: " << i << std::endl;
}

void forward_value(int &&i) {
    process_value(i);
}

class MyString {
private:
    char *_data;
    size_t _len;

    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

public:
    MyString() {
        _data = NULL;
        _len = 0;
    }

    MyString(const char *p) {
        _len = strlen(p);
        _init_data(p);
    }

    MyString(const MyString &str) {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
    }

    MyString(MyString &&str) {
        std::cout << "Move Constructor is called! source: " << str._data << std::endl;
        _len = str._len;
        _data = str._data;
        str._len = 0;
        str._data = NULL;
    }

    MyString &operator=(const MyString &str) {
        if (this != &str) {
            _len = str._len;
            _init_data(str._data);
        }
        std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
        return *this;
    }

    size_t size() {
        return _len;
    }

    virtual ~MyString() {
        if (_data)
            free(_data);
    }
};

struct A {
/*    virtual*/ void a() { cout << "A" << endl; }

    virtual ~A() { cout << "~A()" << endl; }
};

struct B : public A {
    void a() { cout << "B" << endl; }

    virtual ~B() { cout << "~B()" << endl; }
};

template<class T, T v>
struct integral_constant;

using one_type = std::integral_constant<int, 1>;

template<class T>
struct two_type :
        std::integral_constant<int, 2> {
};

int main(void) {
    // Solution s;
    vector<string> v = {"flower", "flow", "flight"};
    cout << v.at(9);
}
