/*
Difficulty: Medium

Given a binary tree, imagine yourself standing on the right side of it, return 
the values of the nodes you can see ordered from top to bottom.

Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
  
  
Solution: Level Traversal
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> vec;
        if (!root) return vec;
        
        queue<TreeNode *> que;
        que.push(root);
        TreeNode *node = root, *prevLast = root, *last = root;
        
        while (!que.empty()) {
            node = que.front();
            if (node->left) {
                que.push(node->left);
                last = node->left;
            }
            if (node->right) {
                que.push(node->right);
                last = node->right;
            }
            if (node == prevLast) {
                vec.push_back(node->val);
                prevLast = last;
            }
            que.pop();
        }
        
        return vec;
    }
};