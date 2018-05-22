/*
Diifculty: Hard

Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node
 to any node in the tree along the parent-child connections. The path must contain at
 least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42

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
    int maxPathSum(TreeNode *root, int &sumMax) {
        if (!root) return 0;
        
        int left = maxPathSum(root->left, sumMax);
        int right = maxPathSum(root->right, sumMax);
        
        // The max sum could be one of the following situations:
        //    1) root + left
        //    2) root + right
        //    3) root
        //    4) root + left + right  
        // And the whole function need to return the the max of 1) 2) 3) 
        
        int val = root->val;
        int sumBranch = left > right ? max(left + val, val) : max(right + val, val);
        int m = max(left + right + val, sumBranch);
        sumMax = max(sumMax, m);
        
        return sumBranch;
    }
    
public:
    int maxPathSum(TreeNode* root) {
        int sumMax = INT_MIN;
        maxPathSum(root, sumMax);
        
        return sumMax;
    }
};