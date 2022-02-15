/* Medium
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

Example 1:
Input: 1->2->3->3->4->4->5
Output: 1->2->5

Example 2:
Input: 1->1->1->2->3
Output: 2->3

Relatives:
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

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode sentinel(0, head);
        auto* pred = &sentinel;

        while (head) {
            if (head->next && head->val == head->next->val) {
                while (head->next && head->val == head->next->val) {
                    head = head->next;
                }
                pred->next = head->next;
            } else {
                pred = pred->next;
            }

            head = head->next;
        }

        return sentinel.next;
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head)
            return nullptr;

        ListNode dummy{0, head};
        ListNode* pre = &dummy, *dup = head, *cur = head;

        while (cur) {
            if (cur->val != dup->val) {
                if (dup->next == cur) {
                    pre = pre->next = dup;
                    dup = cur;
                } else {
                    pre->next = dup = cur;
                }
            }
            cur = cur->next;
        }
        if (dup->next != nullptr) // [1, 1]
            pre->next = nullptr;

        return dummy.next;
    }
};