/*
Difficulty: Hard

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list.
If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:

Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

Note:

Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.
*/

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy{0};
        auto* start = head;
        auto* end = head;
        auto* prevTail = &dummy;

        int i = 0;
        while (end) {
            if (++i % k == 0) {
                ListNode* prev = end->next;
                auto* cur = start;
                auto* next = start;

                while (prev != end) {
                    next = cur->next;
                    cur->next = prev;
                    prev = cur;
                    cur = next;
                }

                prevTail->next = prev;
                prevTail = start;
                prevTail->next = end = start = next;
            } else {
                end = end->next;
            }
        }

        return dummy.next;
    }
};