/*
Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->NULL,
return 1->3->5->2->4->NULL.

Note:
The relative order inside both the even and odd groups should remain as it was in the input. 
The first node is considered odd, the second node even and so on ...
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
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode* pOdd = head;
        ListNode* p = head->next;
        ListNode* pNext = NULL;
        while(p && (pNext=p->next)) {
            
            p->next = pNext->next;
            pNext->next = pOdd->next;
            pOdd->next = pNext;
            
            p = p->next;
            pOdd = pOdd->next;
        
        }
        return head;
    }
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return NULL;
        
        ListNode even(0);
        ListNode *p = head,  *te = &even;
        te->next = head;
        while (p->next && te->next) {
            te = te->next = p->next;
            if (te->next)
                p = p->next = te->next;
        }
        te->next = NULL;
        p->next = even.next;
        
        return head;
    }
};