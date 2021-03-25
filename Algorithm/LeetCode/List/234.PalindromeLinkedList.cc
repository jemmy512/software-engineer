/* Easy
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?

Constraints:
The number of nodes in the list is in the range [1, 10^5].
0 <= Node.val <= 9

Relatives:
009. Palindrome Number
125. Valid Palindrome
234. Palindrome Linked List
680. Valid Palindrome II */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head)
            return false;

        auto* mid = findMid(head);
        auto* lead = reverseList(mid);

        while (head != mid) {
            if (head->val != lead->val) {
                return false;
            }
            head = head->next;
            lead = lead->next;
        }

        return true;
    }

private:
    ListNode* findMid(ListNode* head) {
        auto* fast = head;
        auto* slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverseList(ListNode* head) {
        auto* fast = head;
        auto* mid = head;
        ListNode* tail = nullptr;

        while (mid) {
            fast = mid->next;
            mid->next = tail;
            tail = mid;
            mid = fast;
        }

        return tail;
    }
};
