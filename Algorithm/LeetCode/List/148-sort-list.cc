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
147. Insertion Sort List (insertion sort)
148. Sort list (merge sort)
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

        auto* midPrev = getMidPrev(head);
        auto* left = sortList(head);
        auto* right = sortList(midPrev);

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

    ListNode* getMidPrev(ListNode* head) {
        ListNode dummy(0, head);
        /* the prev of mid, so init value shoule be one step before head */
        auto* prev = &dummy;

        while (head && head->next) {
            prev = prev->next;
            head = head->next->next;
        }

        auto* midPrev = prev->next;
        prev->next = nullptr;

        return midPrev;
    }

    ListNode* getMidOrNext(ListNode* head) {
        // ERROR: AddressSanitizer: stack-overflow
        // [4, 2, 1, 3]
        // head = [4, 2]
        auto* prev = head;

        while (head && head->next) {
            prev = prev->next;
            head = head->next->next;
        }

        // prev = [2], mid = nullptr
        auto* midOrNext = prev->next;
        prev->next = nullptr;

        /* the left part [4, 2] is not partitioned, it is sitll the left part of next recursion,
            which causes dead loop
            4   2   1   3
                        H
                P   M

            4   2   1
                    H
                P   M

            4   2
                    H
                P   M       --> dead looop

            4   2
                    H
                P   M   */

        return midOrNext;
    }
};