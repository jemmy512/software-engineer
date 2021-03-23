/* Easy
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

Constraints:
The number of nodes in the list is in the range [0, 10^4].
1 <= Node.val <= 50
0 <= k <= 50

Relatives:
027. Remove Element
203. Remove Linked List Element
237. Delete Node in a Linked List
283. Move Zeroes */

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // add dummy head to handle the case head's val is equal to val
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *cur = &dummy;

        while (cur->next) {
            if (cur->next->val == val) {
                auto* tar = cur->next;
                cur->next = cur->next->next;
                delete tar;
            } else {
                cur = cur->next;
            }
        }

        return dummy.next;
    }
};