/* Easy
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

Constraints:
The number of nodes in the list is in the range [1, 10^5].
0 <= Node.val <= 9

Relatives:
009. Palindrome Number
125. Valid Palindrome
234. Palindrome Linked List
680. Valid Palindrome II */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
 * Even nodes
    Node -> Node -> Node -> Ndoe ->   ^
                      |               |
                    slow            fast

 * Odd nodes
    Node -> Node -> Node -> Ndoe -> Node
                     |               |
                    slow            fast */

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head)
            return false;

        auto* midOrNext = getMidOrNext(head);
        auto* lead = reverseListForward(midOrNext);

        while (head != midOrNext) {
            if (head->val != lead->val) {
                return false;
            }
            head = head->next;
            lead = lead->next;
        }

        return true;
    }

private:
    ListNode* getMidOrNext(ListNode* head) {
        auto* fast = head;
        auto* slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverseListForward(ListNode* head) {
        auto* fast = head;
        auto* mid = head;
        ListNode* tail = nullptr;

        while (mid) {
            fast = mid->next;
            mid->next = tail;
            tail = mid;
            mid = fast;
        }

        return tail;
    }
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        Beg = head;
        auto* fast = head;
        auto* slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return traverse(slow);
    }

private:
    bool traverse(ListNode* node) {
        if (!node)
            return true;

        auto ret = traverse(node->next);
        ret = ret && (node->val == Beg->val);
        Beg = Beg->next;

        return ret;
    }

private:
    ListNode* Beg = nullptr;
};
