/*
Difficulty: Medium

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?
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
    ListNode *detectCycle(ListNode *head) {
        if (!head) return NULL;
        
        ListNode *fast = head, *slow = head;
        do {
            if (fast->next && fast->next->next) {
                slow = slow->next;
                fast = fast->next->next;
            } else {
                return NULL;
            }
        } while (slow != fast);
        
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        
        return fast;
    }
};