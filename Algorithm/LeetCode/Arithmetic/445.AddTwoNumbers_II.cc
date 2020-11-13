/*
Difficulty: Medium

You are given two non-empty linked lists representing two non-negative integers. 
The most significant digit comes first and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode *> one;
        stack<ListNode *> two;
        
        while (l1) {
            one.push(l1);
            l1 = l1->next;
        }
        while (l2) {
            two.push(l2);
            l2 = l2->next;
        }
        
        int sum = 0;
        ListNode *nd = new ListNode(0);
        while (!one.empty() || !two.empty()) {
            if (!one.empty()) {
                sum += one.top()->val;
                one.pop();
            }
            if (!two.empty()) {
                sum += two.top()->val;
                two.pop();
            }
            nd->val = sum % 10;
            ListNode *head = new ListNode(sum / 10);
            head->next = nd;
            nd = head;
            sum /= 10;
        }
        
        return (nd->val ? nd : nd->next);
    }
};