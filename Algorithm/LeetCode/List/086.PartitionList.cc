/* Medium
Given a linked list and a value x, partition it such that
all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example:
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5

Constraints:
The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less, great;
        auto* tailLess = &less;
        auto* tailGreat = &great;

        while (head) {
            if (head->val < x) {
                tailLess = tailLess->next = head;
            } else {
                tailGreat = tailGreat->next = head;
            }
            head = head->next;
        }

        tailLess->next = great.next;
        tailGreat->next = nullptr;

        return less.next;
    }
};