/**
 Given a binary tree, return the zigzag level order traversal of its nodes' values.
 (ie, from left to right, then right to left for the next level and alternate between).
 *
 For example:
 Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
   return its zigzag level order traversal as:
   [
  [3],
  [20,9],
  [15,7]
]
 */

#include <vector>
#include <queue>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root)
            return levels;

        deque<int> level;
        queue<TreeNode*> que;
        que.push(root);
        TreeNode* preLast = root, *cur, *last;

        while (!que.empty()) {
            cur = que.front();
            que.pop();

            if (isOrderRight)
                level.emplace_back(cur->val);
            else
                level.emplace_front(cur->val);

            if (cur->left) {
                que.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                que.push(cur->right);
                last = cur->right;
            }

            if (cur == preLast) {
                levels.push_back({level.begin(), level.end()});
                level.clear();
                isOrderRight = !isOrderRight;
                preLast = last;
            }
        }

        return levels;
    }

private:
    bool isOrderRight{true};
    vector<vector<int>> levels;
};