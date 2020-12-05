/* Medium
Given a singly linked list where elements are sorted in ascending order, convert
    it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in
    which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:
      0
     / \
   -3   9
   /   /
 -10  5 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return sortedListToBST(head, NULL);
    }

private:
    TreeNode *sortedListToBST(ListNode *head, ListNode *tail) {
        if (head == tail) return NULL;
        if (head->next == tail) return (new TreeNode(head->val));

        ListNode *mid = head, *fast = head; // fast = head->next; 'mid' will be the previous before real node
        while (fast != tail && fast->next != tail) {
            mid = mid->next;
            fast = fast->next->next;
        }

        TreeNode *root = new TreeNode(mid->val);
        root->left = sortedListToBST(head, mid);
        root->right = sortedListToBST(mid->next, tail);

        return root;
    }
};