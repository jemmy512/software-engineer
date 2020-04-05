/*
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
// beat 98.87% 
// take care the cases: m may NULL and m->next may be NULL(ignore this case cause run time error)
bool hasCycle(ListNode *head) {
    ListNode *m = head;
    ListNode *n = head;
    while (m != NULL && m->next != NULL) {
        n = n->next;
        m = m->next->next;
        if (m == n)  return true;
    }
    
    return false;
}