/* Easy
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?

onstraints:
The number of nodes in the list is the range [0, 5000].
-5000 <= Node.val <= 5000

Relatives:
206. Reverse Linked List
092. Reverse Linked List II

024. Swap Nodes in Pairs
025. Reverse Nodes in k-Group
1721. Swapping Nodes in a Linked List */

struct ListNode {
    int val{0};
    ListNode *next{nullptr};
    ListNode(int x) : val(x), next(nullptr) {}
};

/* solution 1: reverse */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        auto* fast = head;
        auto* mid = head;
        ListNode* slow = nullptr;

        while (mid) {
            fast = mid->next;
            mid->next = slow;
            slow = mid;
            mid = fast;
        }

        return slow;
    }
};

/* solution 2: insert
 * Suitable for range based reserve problem:
 *  092. Reverse Linked List II
 *  024. Swap Nodes in Pairs
 *  025. Reverse Nodes in k-Group */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode dummy;
        dummy.next = head;
        auto* slow = &dummy;
        auto* fast = dummy.next;

        while (fast && fast->next) {
            auto* node = fast->next;
            fast->next = node->next;
            node->next = slow->next;
            slow->next = node;
        }

        return dummy.next;
    }
};

/* solution 3: recursion */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        auto* prev = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return prev;
    }
};