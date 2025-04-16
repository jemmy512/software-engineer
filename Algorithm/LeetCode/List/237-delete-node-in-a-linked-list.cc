/* Easy
Write a function to delete a node (except the tail) in a singly linked list,
given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3,
the linked list should become 1 -> 2 -> 4 after calling your function.

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
1836. Remove Duplicates From an Unsorted Linked List

Constraints:
The number of the nodes in the given list is in the range [2, 1000].
-1000 <= Node.val <= 1000
The value of each node in the list is unique.
The node to be deleted is in the list and is not a tail node */

#include<iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};