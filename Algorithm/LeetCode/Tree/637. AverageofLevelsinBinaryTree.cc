/* Easy
Given a non-empty binary tree, return the average value of the nodes on each
level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2
    is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer. */

#include <vector>
#include <queue>
#include <numeric>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> averages;

        getLevlesRecursively(root, 0);
        for (const auto& level : levels) {
            averages.emplace_back(std::accumulate(level.begin(), level.end(), 0.0) / level.size());
        }

        return averages;
    }

private:
    void getLevlesRecursively(TreeNode* root, int curLevel) {
        if (!root)
            return;

        if (levels.size() == curLevel) {
            levels.push_back({});
        }

        levels[curLevel].emplace_back(root->val);

        getLevlesRecursively(root->left, curLevel+1);
        getLevlesRecursively(root->right, curLevel+1);
    }

    void getLevlesIteratively(TreeNode* node) {
        if (!node)
            return;

        vector<int> level;
        TreeNode* preLast = node, *last, *cur;
        queue<TreeNode*> que;
        que.push(node);

        while (!que.empty()) {
            cur = que.front(); que.pop();
            level.emplace_back(cur->val);

            if (cur->left) {
                que.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                que.push(cur->right);
                last = cur->right;
            }

            if (cur == preLast) {
                levels.push_back(level);
                level.clear();
                preLast = last;
            }
        }
    }

private:
    vector<vector<int>> levels;
};