/* Medium
Given a linked list, swap every two adjacent nodes and return its head.

Example:
Given 1->2->3->4, you should return the list as 2->1->4->3.

Note:
Your algorithm should use only constant extra space.
You may not modify the values in the list's nodes, only nodes itself may be changed.

Relatives:
206. Reverse Linked List
092. Reverse Linked List II

024. Swap Nodes in Pairs
025. Reverse Nodes in k-Group
1721. Swapping Nodes in a Linked List */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;

        ListNode dummy;
        dummy.next = head;
        auto* prev = &dummy;

        while (head && head->next) {
            auto* next = head->next;
            head->next = next->next;
            next->next = head;
            prev->next = next;
            prev = head;
            head = head->next;
        }

        return dummy.next;
    }
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        return reverseKGrpu(head, 2);
    }

private:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);

        auto i = 0;
        auto* tail = &dummy;
        auto* beg = head;
        auto* end = head;

        while (end) {
            if (++i % k == 0) {
                while (tail->next != end) {
                    auto* node = beg->next;
                    beg->next = node->next;
                    node->next = tail->next;
                    tail->next = node;
                }

                tail = beg;
                end = beg = beg->next;
            } else {
                end = end->next;
            }
        }

        return dummy.next;
    }
};