/* Medium
Sort a linked list in O(n log n) time using constant space complexity.

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5

Relatives:
021. Merge Two Sorted List
023. Merge k Sorted Lists
088. Merge Sorted Array
148. Sort List
244. Shortest Word Distance II
1634. Add Two Polynomials Represented as Linked Lists */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/* Divide and Conquer Algorithm
 * Time complexity: O(NlogN) */
class Solution {
public:
    ListNode *mergeSortedList(ListNode *left, ListNode *right) {
        ListNode dummy(0);
        dummy.next = left;
        ListNode *tail = &dummy;
        while (left && right) {
            if (right->val < left->val) {
                tail = tail->next = right;
                right = right->next;
            } else {
                tail = tail->next = left;
                left = left->next;
            }
        }
        if (left == NULL)
            tail->next = right;
        else
            tail->next = left;
        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)
            return head;

        ListNode *left = head, *right = head->next;
        while (right && right->next) {
            left = left->next;
            right = right->next->next;
        }

        right = left->next;
        left->next = NULL;
        left = sortList(head);
        right = sortList(right);

        return mergeSortedList(left, right);
    }
};