/*
Difficulty: Easy

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the
 root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) 
            return 1;
        
        int l1 = INT_MAX;
        int l2 = INT_MAX;
        if (root->left)
            l1 =  minDepth(root->left);
        if (root->right)
            l2 = minDepth(root->right);
        
        return (l1 < l2 ? l1 + 1 : l2 + 1);
    }
};