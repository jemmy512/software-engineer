/* Hard
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:
Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6

Relatives:
021. Merge Two Sorted List
023. Merge k Sorted Lists
088. Merge Sorted Array
148. Sort List
244. Shortest Word Distance II
725. Split Linked List in Parts
1634. Add Two Polynomials Represented as Linked Lists */

#include <climits>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/*
1. Pair up k lists and merge each pair.
2. After the first pairing, k lists are merged into k/2 lists with average
    2N/k length, then k/4, k/8 and so on.
3. Repeat this procedure until we get the final sorted linked list.
Thus, we'll traverse almost NN nodes per pairing and merging, and repeat this procedure about \log_{2}{k}
​​ k times. */

/* Merge with Divide And Conquer
 * Time Complexity: O(NlogK), merge two lists use N time complexity, divide use logK time complexity */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }

        auto len = lists.size();
        auto interval = 1;

        while (interval < len) {
            for (auto i = 0; i < len - interval; i += interval*2) {
                lists[i] = merge2List(lists[i], lists[i+interval]);
            }
            interval *= 2;
        }

        return lists[0];
    }

private:
    ListNode* merge2List(ListNode* lhs, ListNode* rhs) {
        ListNode dummy;
        auto* tail = &dummy;

        while (lhs && rhs) {
            auto*& cur = (lhs->val < rhs->val) ? lhs : rhs;
            tail = tail->next = cur;
            cur = cur->next;
        }
        tail = tail->next = lhs ? lhs : rhs;

        return dummy.next;
    }
};

/* Time Complexity: O(KN), where K is the length of the list, N is the complexity of merge two lists */
class Solution_1 {
public:
    ListNode *merge2List(ListNode *lhs, ListNode *rhs) {
        ListNode dummy = ListNode(INT_MAX);
        ListNode *tail = &dummy;

        while (lhs && rhs) {
            if (lhs->val < rhs->val) {
                tail = tail->next = lhs;
                lhs = lhs->next;
            } else {
                tail = tail->next = rhs;
                rhs = rhs->next;
            }
        }
        tail->next = lhs ? lhs : rhs;

        return dummy.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;

        int len = lists.size();
        for (int i = len - 2; i >=0; --i)
            lists[i] = merge2List(lists[i], lists[i+1]);

        return lists[0];
    }
};

class Solution_0 {
public:
    bool isEmpty(vector<ListNode*>& lists) {
        for (ListNode *node : lists) {
            if (node)
                return false;
        }
        return true;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = NULL;
        ListNode *tail = head, *MAX_NODE = new ListNode(INT_MAX);
        ListNode *tmp = MAX_NODE;
        int index, len = lists.size();

        while (!isEmpty(lists)) {
            for (int i = 0; i < len; ++i) {
                if (!lists[i]) {
                    continue;
                }

                if (lists[i]->val < tmp->val) {
                    tmp = lists[i];
                    index = i;
                }
            }
            lists[index] = lists[index]->next;
            if (tmp != MAX_NODE) {
                if (head) {
                    tail = tail->next = tmp;
                } else {
                    head = tail = tmp;
                }
                tmp = MAX_NODE;
            }
        }

        return head;
    }
};
