/* Easy
Given a binary tree, find its minimum depth.

**The minimum depth is the number of nodes along the shortest path from the
 root node down to the nearest leaf node. **

Note: **A leaf is a node with no children.**

Example:

Given binary tree [3,9,20,null,null,15,7],

     3
   /   \
  9     20
   \   /  \
    8 15   7
     |
     8
return its minimum depth = 3 [3, 9, 8]. */

#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* dfs */
class Solution {
public:
    int minDepth(TreeNode* root) {
        return dfs(root);
    }

private:
    int dfs(TreeNode* root) {
        if (!root)
            return 0;

        if (!root->left)
            return dfs(root->right) + 1;
        else if (!root->right)
            return dfs(root->left) + 1;
        else
            return min(dfs(root->left), dfs(root->right)) + 1;
    }
};

/* bfs */
class Solution {
public:
    int minDepth(TreeNode* root) {
        return bfs(root);
    }

private:
    int bfs(TreeNode* root) {
        if (!root)
            return 0;

        int depth = 1;
        queue<TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            auto size = que.size();
            for (auto i = 0; i < size; ++i) {
                auto* node = que.front();
                que.pop();

                if (!node->left && !node->right)
                    return depth;
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }

            ++depth;
        }

        return depth;
    }
};