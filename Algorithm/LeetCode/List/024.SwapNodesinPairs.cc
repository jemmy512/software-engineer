/* Medium
Given a linked list, swap every two adjacent nodes and return its head.

Example:
Given 1->2->3->4, you should return the list as 2->1->4->3.

Note:
Your algorithm should use only constant extra space.
You may not modify the values in the list's nodes, only nodes itself may be changed.

Relatives:
024. Swap Nodes in Pairs
025. Reverse Nodes in k-Group
1721. Swapping Nodes in a Linked List */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;

        ListNode *node = head;
        while (node && node->next) {
            swap(node->val, node->next->val);
            node = node->next->next;
        }

        return head;
    }
};