/* Medim
Given the head of a linked list, find all the values
that appear more than once in the list and delete the nodes that have any of those values.
Return the linked list after the deletions.

Example 1:
Input: head = [1,2,3,2]
Output: [1,3]
Explanation: 2 appears twice in the linked list,
so all 2's should be deleted. After deleting all 2's, we are left with [1,3].

Example 2:
Input: head = [2,1,1,2]
Output: []
Explanation: 2 and 1 both appear twice. All the elements should be deleted.

Example 3:
Input: head = [3,2,2,1,3,2,4]
Output: [1,4]
Explanation: 3 appears twice and 2 appears three times.
After deleting all 3's and 2's, we are left with [1,4].

Constraints:
The number of nodes in the list is in the range [1, 105]
1 <= Node.val <= 105

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

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * }; */

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode dummy(0, head);
        std::unordered_map<int, int> freq;
        auto* fast = head;
        auto* slow = &dummy;

        while (fast) {
            ++freq[fast->val];
            fast = fast->next;
        }

        fast = head;
        while (fast) {
            if (freq[fast->val] > 1) {
                slow->next = fast->next;
            } else {
                slow = fast;
            }
            fast = fast->next;
        }

        return dummy.next;
    }
};