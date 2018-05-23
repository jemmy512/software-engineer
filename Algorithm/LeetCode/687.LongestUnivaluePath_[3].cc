/*
Diifuclty: Easy

Given a binary tree, find the length of the longest path where each node in the 
path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
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
private:
    int path(TreeNode *root, int val, int &pathMax) {
        if (!root) return 0;
        
        int left = path(root->left, root->val, pathMax);
        int right = path(root->right, root->val, pathMax);
        pathMax = max(pathMax, left + right);
        
        if (root->val == val) return max(left, right) + 1;
        return 0;
    }
    
public:
    int longestUnivaluePath(TreeNode* root) {
        if (!root) return 0;
        
        int pathMax = INT_MIN;
        path(root, root->val, pathMax);
        
        return pathMax;
    }
};

class Solution_ {
public:
    int path(TreeNode *root, int &pathMax) {
        if (!root || !root->left && !root->right) return 0;
        
        int left = path(root->left, pathMax);
        int right = path(root->right, pathMax);
        
        int val = root->val;
        int l = 0, r = 0;
        if (root->left && root->left->val == val) {
            l = left + 1;
        } 
        if (root->right && root->right->val == val) {
            r = right + 1;
        } 

        int pathBranch = max(l, r);
        if (root->left && root->right && root->left->val == val && root->right->val == val) {
            pathMax = max(pathMax, left + right + 2);
        } else {
             pathMax = max(pathMax, pathBranch);
        }

        return pathBranch;
    }
    
    int longestUnivaluePath(TreeNode* root) {
        int pathMax = INT_MIN;
        path(root, pathMax);
        
        return max(pathMax, 0);
    }
};