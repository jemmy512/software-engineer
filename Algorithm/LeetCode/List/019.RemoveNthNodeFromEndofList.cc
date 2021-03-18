/* Medium
Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?

Relative:
1474. Delete N Nodes After M Nodes of a Linked List
1721. Swapping Nodes in a Linked List */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// beat 35.03%
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *prev = head;
    ListNode *last = head;

    while (prev != NULL) {
        prev = prev->next;
        if (n-- < 0) {
            last = last->next;
        }
    }

    if (n)
        last->next = last->next->next;
    else
        head = head->next;

    return head;
}

// beat 5.87%
ListNode* removeNthFromEnd_1(ListNode* head, int n) {
    ListNode *m = head;
    ListNode *l = head;

    while (m != NULL && n) {
        m = m->next;
        --n;
    }
    while (m != NULL && m->next != NULL) {
        m = m->next;
        l = l->next;
    }
    if (m == NULL)
        head = head->next;
    else
        l->next = l->next->next;
    return head;
}