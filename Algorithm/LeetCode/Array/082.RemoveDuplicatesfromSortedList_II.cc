/*
Difficulty: Medium

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        
        long duplicate;
        ListNode dummy(0);
        ListNode *first = &dummy, *second = head;
        first->next = head;
        while (second) {
            if (second->next && (second->val == second->next->val || second->val == duplicate)) {
                if (second->val != duplicate)
                    duplicate = second->val;
            } else {
                if (second->val != duplicate)
                    first = first->next = second;
            }
            second = second->next;
        }
        first->next = second;
        
        return dummy.next;
    }
};