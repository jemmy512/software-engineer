/*
Difficulty: Easy

Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
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
    void leftCount(TreeNode *root, int lr, int &ret) {
        // lr indicate left or ri

        if (!root->left && !root->right && lr)
            ret += root->val;
        if (root->left) 
            leftCount(root->left, 1, ret);
        if (root->right) 
            leftCount(root->right, 0, ret);
    }
    
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        
        int ret = 0;
        leftCount(root, 0, ret);
        
        return ret;
    }
};