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

Relatives:
053. Maximum Subarray
112. Path Sum
113. Path Sum II
437. Path Sum III
666. Path Sum IV
124. Binary Tree Maximum Path Sum
129. Sum Root to Leaf Numbers
687. Longest Univalue Path
1376. Time Needed to Inform All Employees */

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
        vector<int> path;
        pathSum(root, sum, path);

        return result;
    }

private:
    void dfs(TreeNode* node, int sum, vector<int>& path) {
        if (!node)
            return;

        sum -= node->val;
        path.emplace_back(node->val);

        if (!node->left && !node->right && !sum)
            result.push_back(path);

        dfs(node->left, sum, path);
        dfs(node->right, sum, path);

        path.pop_back();
    }

private:
    vector<vector<int>> result;
};