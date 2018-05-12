/*
Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3

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
    void traverse(TreeNode *root, vector<string> &vec, string path) {
        if (!root) return;
        
        if (!path.empty())
            path +=  "->";
        path += to_string(root->val);

        if (!root->left && !root->right) {
            vec.push_back(path);
        } else {
            traverse(root->left, vec, path);
            traverse(root->right, vec, path);
        }
    }
    
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> vec;
        if (!root)
            return vec;
        
        string path;
        traverse(root, vec, path);
        
        return vec;
    }
};