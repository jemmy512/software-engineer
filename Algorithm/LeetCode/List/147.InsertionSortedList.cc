/* Medium
Sort a linked list using insertion sort.

A graphical example of insertion sort.
The partial sorted list (black) initially contains only the prev element in the list.
With each iteration one element (red) is removed from the input data and inserted
in-place into the sorted list

Algorithm of Insertion Sort:
Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
At each iteration, insertion sort removes one element from the input data,
finds the location it belongs within the sorted list, and inserts it there.
It repeats until no input elements remain.

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5

Constraints:
The number of nodes in the list is in the range [1, 5000].
-5000 <= Node.val <= 5000

Relatives:
147. Insertion Sort List (insertion sort)
148. Sort list (merge sort)
708. Insert into a Sorted Circular Linked List */

#include <climits>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
 };

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        while (head) {
            auto* next = head->next;
            auto* pos = findPos(head);
            insertNode(pos, head);
            head = next;
        }

        return dummy.next;
    }

private:
    ListNode* findPos(ListNode* node) {
        auto* cur = &dummy;
        auto* prev = cur;

        while (cur && node->val > cur->val) {
            prev = cur;
            cur = cur->next;
        }

        return prev;
    }

    void insertNode(ListNode* pos, ListNode* node) {
        node->next = pos->next;
        pos->next = node;
    }

private:
    ListNode dummy{INT_MIN};
};
