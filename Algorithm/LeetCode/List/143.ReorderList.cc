/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:

    ListNode *findMid(ListNode *head) {
        ListNode *prev = head, *mid = head, *ret = NULL;
        while (prev && prev->next)  { // odd, even case
            ret = mid;
            mid = mid->next;
            prev = prev->next->next;
        }

        return ret;
    }

    ListNode *reverseList(ListNode *head) {
        ListNode *tail = NULL, *cur = head, *prev;
        while (cur) {
            prev = cur->next;
            cur->next = tail;
            tail = cur;
            cur = prev;
        }

        return tail;
    }

    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        ListNode *mid = findMid(head);
        ListNode *hd = reverseList(mid->next);
        mid->next = NULL;
        ListNode *tail = head, *prev = NULL, *tailPrev;
        while (tail && hd) {
            prev = hd->next;
            hd->next = tail->next;
            tail->next = hd;
            tailPrev = tail->next;
            tail = tail->next->next;
            hd = prev;
        }
        tailPrev->next = hd;
    }
};