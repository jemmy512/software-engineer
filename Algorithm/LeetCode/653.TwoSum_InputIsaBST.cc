/*
Difficulty: Easy

Given a Binary Search Tree and a target number, return true if there exist two 
elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

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
    bool findTarget(TreeNode* root, int k) {
        vector<int> vec;
        stack<TreeNode *> stk;
        TreeNode *cur = root;
        while (!stk.empty() || cur) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top()->right;
                vec.push_back(stk.top()->val);
                stk.pop();
            }
        }
        
        int i = 0, j = vec.size() - 1;
        while (i < j) {
            if (vec[i] + vec[j] == k)
                return true;
            else if (vec[i] + vec[j] < k)
                ++i;
            else 
                --j;
        }
        
        return false;
    }
};