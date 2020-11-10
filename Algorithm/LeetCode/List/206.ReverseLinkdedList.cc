/*
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// beat 98.94%
ListNode* reverseList(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode *first = head->next;
    ListNode *last = NULL;

    while (first != NULL) {
        head->next = last;
        last = head;
        head = first;
        first = first->next;
    }
    head->next = last;

    return head;
}