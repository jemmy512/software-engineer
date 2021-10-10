/* Medium
Given the head of a linked list, return the list after sorting it in ascending order.
Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

Example 1:
Input: 4->2->1->3
Output: 1->2->3->4

Example 2:
Input: -1->5->3->4->0
Output: -1->0->3->4->5

Constraints:
The number of nodes in the list is in the range [0, 5 * 10^4].
-10^5 <= Node.val <= 10^5

Relatives:
021. Merge Two Sorted List
023. Merge k Sorted Lists
088. Merge Sorted Array
148. Sort List
244. Shortest Word Distance II
1634. Add Two Polynomials Represented as Linked Lists */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Divide and Conquer Algorithm
 * Time complexity: O(NlogN) */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)
            return head;

        auto* mid = getMid(head);
        auto* left = sortList(head);
        auto* right = sortList(mid);

        return merge(left, right);
    }

private:
    ListNode* merge(ListNode *left, ListNode *right) {
        ListNode dummy(0);
        dummy.next = left;
        ListNode *tail = &dummy;

        while (left && right) {
            auto*& node = (left->val < right->val) ? left : right;
            tail = tail->next = node;
            node = node->next;

        }
        tail->next = left ? left : right;

        return dummy.next;
    }

    ListNode* getMid(ListNode* head) {
        ListNode dummy(0, head);
        auto* prev = &dummy;

        while (head && head->next) {
            prev = prev->next;
            head = head->next->next;
        }

        auto* mid = prev->next;
        prev->next = nullptr;

        return mid;
    }
};