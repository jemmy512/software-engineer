/*
Difficulty: Easy

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.
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
 
// Recursive Solution
class Solution {
public:
    bool symmetricTree(TreeNode *left, TreeNode *right) {
        if (!left && !right) return true;
        if (!left || !right) return false;
        
        return left->val == right->val && symmetricTree(left->left, right->right) && symmetricTree(left->right, right->left);
       
    }
    
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        
        return symmetricTree(root->left, root->right); 
    }
};

// Iterative Solution 
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        
        stack<TreeNode *> stk;
        TreeNode *left, *right;
        stk.push(root->left);
        stk.push(root->right);
        
        while (!stk.empty()) {
            left = stk.top();
            stk.pop();
            right = stk.top();
            stk.pop();
            if (!left && !right) continue;
            if (!left || !right) return false;
            if (left->val - right->val) return false;
            
            stk.push(left->right);
            stk.push(right->left);
            
            stk.push(left->left);
            stk.push(right->right);
        }
        
        return true;
    }
};