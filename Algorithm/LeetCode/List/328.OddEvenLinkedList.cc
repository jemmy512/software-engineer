/* Medium
Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example:
Given 1->2->3->4->5->nullptr,
return 1->3->5->2->4->nullptr.

Note:
The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on ... */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head)
            return nullptr;

        ListNode* odd = head;
        ListNode* even = head->next;
        ListNode* evenHead = even;

        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;

        return head;
    }
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head)
            return head;

        ListNode* oddTail = head;
        ListNode* evenHead = head->next;
        ListNode* evenNext = nullptr;

        while (evenHead && evenHead->next) {
            evenNext = evenHead->next;
            evenHead->next = evenNext->next;
            evenNext->next = oddTail->next;
            oddTail->next = evenNext;

            evenHead = evenHead->next;
            oddTail = oddTail->next;
        }

        return head;
    }
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return nullptr;

        ListNode even(0);
        ListNode *evenHead = head,  *te = &even;
        te->next = head;
        while (evenHead->next && te->next) {
            te = te->next = evenHead->next;
            if (te->next)
                evenHead = evenHead->next = te->next;
        }
        te->next = nullptr;
        evenHead->next = even.next;

        return head;
    }
};