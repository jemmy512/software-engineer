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
        ListNode dummy{0};
        dummy.next = head;
        auto* groupBeg = head; // [groupBeg, groupEnd]
        auto* groupEnd = head;
        auto* listTail = &dummy;

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
}