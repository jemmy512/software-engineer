/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:

Input:
    2
   / \
  1   3
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
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

// 75 test cases, 11ms, beat 72.74%
// Recursive Version
class Solution {
public:
	bool isValidBST(TreeNode* root) {
		return validateBST(root, LLONG_MIN, LLONG_MAX);
	}
	
private:
	bool validateBST(TreeNode* node, long min, long max) {
		if(!node) return true;
		if(node->val <= min || node->val >= max) return false;
		return validateBST(node->left, min, node->val) 
				&& validateBST(node->right, node->val, max);
	}
};
 
// 75 test cases, 13ms, beat 26.77%
// Iterative Version
class Solution {
public:
    bool isValidBST(TreeNode* root) {
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
        int len = vec.size();
        for (int i = 0; i <= len - 2; ++i) {
            if (vec[i] >= vec[i+1])
                return false;
        }
        
        return true;
    }
};