/* Hard
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list.
If the number of nodes is not a multiple of k then left-out nodes in the groupEnd should remain as it is.

Example:
Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5

Note:
Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.

Constraints:
The number of nodes in the list is in the range sz.
1 <= sz <= 5000
0 <= Node.val <= 1000
1 <= k <= sz

Relatives:
206. Reverse Linked List
092. Reverse Linked List II

024. Swap Nodes in Pairs
025. Reverse Nodes in k-Group
1721. Swapping Nodes in a Linked List */

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy{0};
        dummy.next = head;
        auto* groupBeg = head; // [groupBeg, groupEnd]
        auto* groupEnd = head;
        auto* listTail = &dummy;

        /* only works when 1 <= k <= sz */
        int i = 0;
        while (groupEnd) {
            if (++i % k == 0) {
                auto* slow = groupEnd->next;
                auto* mid = groupBeg;
                auto* fast = groupBeg;

                while (slow != groupEnd) {
                    fast = mid->next;
                    mid->next = slow;
                    slow = mid;
                    mid = fast;
                }

                listTail->next = groupEnd;
                listTail = groupBeg;
                groupBeg = groupEnd = fast;
            } else {
                groupEnd = groupEnd->next;
            }
        }

        return dummy.next;
    }
};