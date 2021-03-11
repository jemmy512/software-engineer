/* Medium
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

#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> paths;
        vector<int> path;
        pathSum(root, 0, sum, paths, path);

        return paths;
    }

private:
    void pathSum(TreeNode *root, int curSum, int sum, vector<vector<int>>& paths, vector<int>& path) {
        if (!root) return;

        curSum += root->val;
        path.push_back(root->val);

        bool isLeaf = !root->left && !root->right;
        if (isLeaf && curSum == sum) {
            paths.push_back(path);
            path.pop_back();
            return;
        }

        if (root->left) {
            pathSum(root->left, curSum, sum, paths, path);
        }
        if (root->right) {
            pathSum(root->right, curSum, sum, paths, path);
        }

        curSum -= root->val;
        path.pop_back();
    }
};