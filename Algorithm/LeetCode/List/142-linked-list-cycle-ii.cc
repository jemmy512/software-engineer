/* Medium
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached
again by continuously following the next pointer.
Internally, pos is used to denote the index of the node that tail's next pointer is connected to.

Note that pos is not passed as a parameter.

Notice that you should not modify the linked list.

Follow up: Can you solve it without using extra space?

Constraints:
The number of the nodes in the list is in the range [0, 10^4].
-10^5 <= Node.val <= 10^5
pos is -1 or a valid index in the linked-list.

Relative:
141. Linked List Cycle
142. Linked List Cycle II
287. Findthe Duplicate Number

Approches:
1. Floyd's slow and fast
2. Hash table */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head)
            return nullptr;

        auto* fast = head;
        auto* slow = head;

        do {
            if (fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
            } else {
                return nullptr;
            }
        } while (fast != slow);

        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }

        return fast;
    }
};