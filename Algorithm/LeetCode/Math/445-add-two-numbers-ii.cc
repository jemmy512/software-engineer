/* Medium
You are given two non-empty linked lists representing two non-negative integers.
The most significant digit comes first and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

Relatives:
002. Add Two Numbers
445. Add Two Numbers II
1634. Add Two Polynomials Represented as Linked Lists */

#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode*> one;
        stack<ListNode*> two;

        while (l1) {
            one.push(l1);
            l1 = l1->next;
        }
        while (l2) {
            two.push(l2);
            l2 = l2->next;
        }

        int sum = 0;
        auto* head = new ListNode(0);

        while (!one.empty() || !two.empty()) {
            if (!one.empty()) {
                sum += one.top()->val;
                one.pop();
            }
            if (!two.empty()) {
                sum += two.top()->val;
                two.pop();
            }
            head->val = sum % 10;
            auto* node = new ListNode(sum/10);
            node->next = head;
            head = node;
            sum /= 10;
        }

        return (head->val ? head : head->next);
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto* head = add(l1, l2);
        return head->val ? head : head->next;
    }

private:
    ListNode* add(ListNode* l1, ListNode* l2) {
        if (!l1 && !l2)
            return nullptr;

        auto* next = add(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr);
        int sum = 0;
        if (next)
            sum += next->val;
        if (l1)
            sum += l1->val;
        if (l2)
            sum += l2->val;

        ListNode* node = nullptr;
        if (next) {
            node->val = sum % 10;
        } else {
            node = new ListNode(sum % 10);
        }
        auto* head = new ListNode(sum / 10);
        head->next = node;

        return head;
    }
};

/* [5] [5] */