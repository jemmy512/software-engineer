/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
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
    void pathSum(TreeNode *root, int curSum, int sum, vector<vector<int>> &vvec, vector<int> &vec) {
        if (!root) return;
        
        curSum += root->val;
        vec.push_back(root->val);
        
        bool isLeaf = !root->left && !root->right;
        if (isLeaf && curSum == sum) {
            vvec.push_back(vector<int>(vec.begin(), vec.end()));
            vec.pop_back();
            return;
        }
        
        if (root->left) {
            pathSum(root->left, curSum, sum, vvec, vec);
        }
        if (root->right) {
            pathSum(root->right, curSum, sum, vvec, vec);
        }
        
        curSum -= root->val;
        vec.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> vvec;
        vector<int> vec;
        pathSum(root, 0, sum, vvec, vec);
        
        return vvec;
    }
};