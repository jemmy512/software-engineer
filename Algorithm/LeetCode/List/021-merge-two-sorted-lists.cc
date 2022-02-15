/* Easy
Merge two sorted linked lists and return it as a new list. The new list should
be made by splicing together the nodes of the first two lists.
Example:
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

Relatives:
021. Merge Two Sorted List
023. Merge k Sorted Lists
088. Merge Sorted Array
148. Sort List
244. Shortest Word Distance II
725. Split Linked List in Parts
1634. Add Two Polynomials Represented as Linked Lists */

#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/* Hight performence */
// 13ms, beats 86.61%
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr)
        return l2;
    if (l2 == nullptr)
        return l1;

    ListNode head = ListNode(INT_MIN);
    ListNode *tail = &head;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail = tail->next = l1;
            l1 = l1->next;
        } else {
            tail = tail->next = l2;
            l2 = l2->next;
        }
    }
    tail->next = l1 ? l1 : l2;

    return head.next;
}

// 14ms, beats 60.01%
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode *tail = &dummy;

    while (l1 && l2) {
        ListNode*& node = l1->val < l2->val ? l1 : l2;
        tail = tail->next = node;
        node = node->next;
    }
    tail->next = l1 ? l1 : l2;

    return dummy.next;
}

ListNode* mergeTwoLists_recursive(ListNode* l1, ListNode* l2) {
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    if(l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l2->next, l1);
        return l2;
    }
}