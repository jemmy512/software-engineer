/* Medium

Reverse a linked list from position m to n. Do it in one-pass.

Note: 1 ≤ m ≤ n ≤ length of list.

Example:
Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

Constraints:
The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n

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
 };

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (!head || m >= n) {
            return head;
        }

        ListNode dummy(0);
        dummy.next = head;
        ListNode *fast = dummy.next, *slow = &dummy, *node = nullptr;

        while (--m && --n)
            slow = slow->next;
        fast = slow->next;

        while (--n) {
            node = fast->next;
            fast->next = node->next;
            node->next = slow->next;
            slow->next = node;
        }

        return dummy.next;
    }
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        auto* begPrev = &dummy;
        auto* end = &dummy;

        while (--left > 0) {
            begPrev = begPrev->next;
        }

        while (right-- > 0) {
            end = end->next;
        }

        reverseListBackward(begPrev, end);

        return dummy.next;
    }

private:
    // begPrev -> [beg -> ... -> end]
    void reverseListBackward(ListNode* begPrev, ListNode* end) {
        auto* newEnd = begPrev->next;

        while (begPrev->next != end) {
            auto* n = newEnd->next;
            newEnd->next = n->next;
            n->next = begPrev->next;
            begPrev->next = n;
        }
    }
};