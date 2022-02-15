/* Medium
Given a singly linked list L: L0->L1->...->Ln-1->Ln,
reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->...

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:
Given 1->2->3->4, reorder it to 1->4->2->3.

Example 2:
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

Constraints:
The number of nodes in the list is in the range [1, 5 * 10^4].
1 <= Node.val <= 1000 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        auto* mid = findMiddle(head);
        auto* lead = reverseList(mid->next);
        mid->next = nullptr;

        auto* headTail = head;
        auto* leadTail = lead;

        while (headTail && leadTail) {
            leadTail = lead->next;
            lead->next = headTail->next;
            headTail->next = lead;
            headTail = lead->next;
            lead = leadTail;
        }
    }

private:
    ListNode* findMiddle(ListNode* root) {
        auto* fast = root;
        auto* slow = root;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverseList(ListNode* root) {
        auto* fast = root;
        auto* mid = root;
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