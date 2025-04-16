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
1 <= Node.val <= 1000

This problem is a combination of these three easy problems:
876. Middle of the Linked List
206. Reverse Linked List
021. Merge Two Sorted Lists

234. Palindrome Linked List

 * Even nodes
    Node -> Node -> Node -> Node ->   ^
                      |               |
                    slow            fast

 * Odd nodes
    Node -> Node -> Node -> Node -> Node
                     |               |
                    slow            fast */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#include <utility>
#include <tuple>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool GET_MID_OR_NEXT = true;

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* lead = nullptr;

        if (GET_MID_OR_NEXT){
            auto* midOrNext = getMidOrNext(head);
            lead = reverseListForward(midOrNext->next);
            midOrNext->next = nullptr;
        } else {
            auto [midPrev, end] = getMidPrevEnd(head);
            if (!midPrev) {
                return;
            }

            reverseListBackward(midPrev, end);
            lead = midPrev->next;
            midPrev->next = nullptr;
        }

        if (GET_MID_OR_NEXT) {
            spliceListMidNext(head, lead);
        } else {
            spliceListMidPrev(head, lead);
        }
    }

private:
    void spliceListMidNext(ListNode* head, ListNode* lead) {
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

    void spliceListMidPrev(ListNode* head, ListNode* lead) {
        auto* headTail = head;
        auto* leadTail = lead;

        while (headTail && leadTail) {
            leadTail = lead->next;
            lead->next = headTail->next;
            headTail->next = lead;
            headTail = lead->next;
            // The list is splicted by prev middle node, so the left child is shorter
            // than right child. The last one on lead is not spliced when headTail is null
            // 1 -   - 2
            //     5     - 4 - 3
            //
            //         | headTail
            // 1 - 5 - 2
            //           - 4 -      3
            //             |lead    |leadTail
            if (headTail) {
                headTail = lead->next;
            } else {
                lead->next = leadTail;
            }
            lead = leadTail;
        }
    }

    ListNode* getMidOrNext(ListNode* root) {
        auto* fast = root;
        auto* slow = root;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverseListForward(ListNode* head) {
        ListNode* slow = nullptr;
        auto* mid = head;
        auto* fast = head;

        while (mid) {
            fast = mid->next;
            mid->next = slow;
            slow = mid;
            mid  = fast;
        }

        return slow;
    }

    tuple<ListNode*, ListNode*> getMidPrevEnd(ListNode* head) {
        if (!head) {
            return {nullptr, nullptr};
        }
        if (!head->next) {
            return {nullptr, head};
        }

        ListNode dummy{0, head};
        ListNode* prev = &dummy;
        ListNode* fast = head;
        ListNode* end = head;

        while (fast && fast->next) {
            prev = prev->next;
            end = fast->next;
            fast = fast->next->next;
            if (fast) {
                end = fast;
            }
        }

        return {prev, end};
    }

    void reverseListBackward(ListNode* begPrev, ListNode* end) {
        if (!begPrev) {
            return;
        }

        auto* newEnd = begPrev->next;

        while (begPrev->next != end) {
            auto* n = newEnd->next;
            newEnd->next = n->next;
            n->next = begPrev->next;
            begPrev->next = n;
        }
    }
};

// recursion slution
class Solution {
public:
    void reorderList(ListNode* head) {
        Tail = head;
        recursion(getMidOrNext(head));
    }

private:
    void recursion(ListNode* node) {
        if (!node)
            return;

        recursion(node->next);

        if (Tail == node || Tail->next == node) {
            node->next = nullptr;
            return;
        }

        node->next = Tail->next;
        Tail->next = node;
        Tail = Tail->next->next;
    }

    ListNode* getMidOrNext(ListNode* node) {
        auto* slow = node;
        auto* fast = node;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

private:
    ListNode* Tail;
};