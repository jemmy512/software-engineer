/* Medium
Given a linked list, remove the n-th node from the end of list and return its head.

Example:
Given linked list: 1->2->3->4->5, and n = 2.
After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
Given n will always be valid.

Follow up:
Could you do this in one pass?

Constraints:
The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz

Relative:
019. Remove Nth Node From End of List
027. Remove Element
026. Remove Duplicates from Sorted Array
080. Remove Duplicates from Sorted Array II
083. Remove Duplicates from Sorted List
082. Remove Duplicates from Sorted List II
203. Remove Linked List Elements
237. Delete Node In A Linked List
283. Move Zeroes
1474. Delete N Nodes After M Nodes of a Linked List
1721. Swapping Nodes in a Linked List
1836. Remove Duplicates From an Unsorted Linked List */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy;
    dummy.next = head;

    auto* fast = &dummy;
    auto* slow = &dummy;

    while (fast) {
        fast = fast->next;
        if (n-- < 0) { // n-- get previous node of the node to be deleted
            slow = slow->next;
        }
    }

    slow->next = slow->next->next;

    return dummy.next;
}

ListNode* removeNthFromEnd_1(ListNode* head, int n) {
    auto* fast = head;
    auto* slow = head;

    while (fast != nullptr && n) {
        fast = fast->next;
        --n;
    }
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    if (fast == nullptr)
        head = head->next;
    else
        slow->next = slow->next->next;

    return head;
}