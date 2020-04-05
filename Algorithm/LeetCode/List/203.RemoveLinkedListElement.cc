/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/
#includ<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // add dummy head to handle the case head's val is equal to val
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *p = &dummy;
        
        while (p->next) {
            if (p->next->val == val)
                p->next = p->next->next;
            else 
                p = p->next;
        }
       
        return dummy.next;
    }
};