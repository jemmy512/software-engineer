/* Easy
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?

Relatives:
206. Reverse Linked List
092. Reverse Linked List II */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        auto* fast = head;
        auto* mid = head;
        ListNode* slow = nullptr;

        while (mid) {
            fast = mid->next;
            mid->next = slow;
            slow = mid;
            mid = fast;
        }

        return slow;
    }
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        auto* prev = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return prev;
    }
};