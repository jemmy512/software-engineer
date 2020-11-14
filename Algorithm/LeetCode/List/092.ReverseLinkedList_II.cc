/*
Difficulty: Medium

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
 };

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (!head) {
            return nullptr;
        }

        ListNode dummy(0);
        dummy.next = head;
        ListNode *first = dummy.next, *last = &dummy, *node = nullptr;

        while (--m && --n)
            last = last->next;
        first = last->next;

        while (--n) {
            node = first->next;
            first->next = node->next;
            node->next = last->next;
            last->next = node;
        }

        return dummy.next;
    }
};