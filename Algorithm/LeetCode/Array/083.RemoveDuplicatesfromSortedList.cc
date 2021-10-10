/* Easy
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3. 

Relatives:
019. Remove Nth Node From End of List
027. Remove Element
026. Remove Duplicates from Sorted Array
080. Remove Duplicates from Sorted Array II
083. Remove Duplicates from Sorted List
082. Remove Duplicates from Sorted List II 
203. Remove Linked List Elements
237. Delete Node In A Linked List
283. Move Zeroes
1474. Delete N Nodes After M Nodes of a Linked List
1721. Swapping Nodes in a Linked List 
1836. Remove Duplicates From an Unsorted Linked List */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        auto* cur = head;

        while (cur && cur->next) {
            if (cur->val == cur->next->val) {
                cur->next = cur->next->next;
            } else {
                cur = cur->next;
            }
        }

        return head;
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head)
            return nullptr;

        auto* tail = head;
        auto* cur = head->next;

        while (cur) {
            if (cur->val != tail->val) {
                tail = tail->next = cur;
            }
            cur = cur->next;
        }

        tail->next = nullptr;

        return head;

    }
};