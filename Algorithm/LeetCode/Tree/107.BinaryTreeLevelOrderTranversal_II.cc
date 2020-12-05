/* Easy
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
] */

#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (!root)
            return levels;

        levelOrder(root, 0);
        std::reverse(levels.begin(), levels.end());

        return levels;
    }

private:
    void levelOrder(TreeNode* node, int level) {
        if (levels.size() == level)
            levels.push_back({});

        levels[level].emplace_back(node->val);

        if (node->left)
            levelOrder(node->left, level+1);
        if (node->right)
            levelOrder(node->right, level+1);
    }

private:
    vector<vector<int>> levels;
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> vvec;
        if (!root)
            return vvec;

        queue<TreeNode *> nodes;
        TreeNode *pre_last = root, *last, *cur;
        nodes.push(root);
        vector<int> row;

        while (!nodes.empty()) {
            cur = nodes.front();
            row.push_back(cur->val);
            if (cur->left) {
                nodes.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                nodes.push(cur->right);
                last = cur->right;
            }
            if (cur == pre_last) {
                // vvec.insert(vvec.begin(), row);
                vvec.push_back(row);
                row.clear();
                pre_last = last;
            }
            nodes.pop();
        }

        reverse(vvec.begin(), vvec.end());
        return vvec;
    }
};