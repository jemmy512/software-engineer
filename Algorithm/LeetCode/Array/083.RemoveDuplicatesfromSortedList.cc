/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/



// beat 99.34%
ListNode* deleteDuplicates(ListNode* head) {
    ListNode *p = head;
    ListNode *t = head;
    while (p != NULL && p->next != NULL) {
        t = p->next;
        if (p->val == t->val) {
            p->next = t->next;
            free(t);
        } else 
            p = p->next;
    }
    
    return head;
}