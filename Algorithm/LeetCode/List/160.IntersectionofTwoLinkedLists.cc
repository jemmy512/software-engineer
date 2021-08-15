/* Easy
Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.

Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

Constraints:
The number of nodes of listA is in the m.
The number of nodes of listB is in the n.
0 <= m, n <= 3 * 10^4
1 <= Node.val <= 10^5
0 <= skipA <= m
0 <= skipB <= n
intersectVal is 0 if listA and listB do not intersect.
intersectVal == listA[skipA + 1] == listB[skipB + 1] if listA and listB intersect.

Relatives:
160. Internsection of Two Linked Lists
599. Minimum Index Sum of Two Lists */

#include <cmath>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
        auto* nodeA = headA;
        auto* nodeB = headB;

        while (nodeA != nodeB) {
            nodeA = nodeA ? nodeA->next : headB;
            nodeB = nodeB ? nodeB->next : headA;
        }

        return nodeA;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = getListLength(headA);
        int lenB = getListLength(headB);
        if (lenA <= 0 || lenB <= 0)
            return nullptr;

        if (lenA < lenB)
            swap(headA, headB); // headA always points to the longer one.
        for (int i = 0; i < abs(lenA - lenB); ++i)
            headA = headA->next;
        while (headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }

        return headA;
    }

    ListNode *getIntersectionNode_1(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> hash;

        for (auto a = headA; a; a = a-> next)
            hash.insert(a);
        for (auto b = headB; b; b = b-> next)
            if (hash.find(b) != hash.end())
                return b;
        return nullptr;
    }

private:
    int getListLength(ListNode *head) {
        int len = 0;

        while (head) {
            ++len;
            head = head->next;
        }

        return len;
    }
};