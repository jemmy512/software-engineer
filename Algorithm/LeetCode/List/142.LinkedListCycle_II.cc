/*
Difficulty: Medium

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

Relative:
141 linked List Cycle
287 Findthe Duplicate Number

Approches:
1. Floyd's tortoise and hare
2. Hash table */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return NULL;

        ListNode *hare = head, *tortoise = head;
        do {
            if (hare->next && hare->next->next) {
                tortoise = tortoise->next;
                hare = hare->next->next;
            } else {
                return NULL;
            }
        } while (tortoise != hare);

        hare = head;
        while (hare != tortoise) {
            hare = hare->next;
            tortoise = tortoise->next;
        }

        return hare;
    }
};