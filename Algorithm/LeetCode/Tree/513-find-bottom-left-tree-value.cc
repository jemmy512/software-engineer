/* Medium
Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2:
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL. */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        int ret = 0;

        deque<TreeNode*> dque;
        dque.push_back(root);

        while (!dque.empty()) {
            const auto size = dque.size();
            ret = dque.front()->val;

            while (size--) {
                auto* node = dque.front();
                dque.pop_front();

                if (node->left)
                    dque.push_back(node->left);
                if (node->right)
                    dque.push_back(node->right);
            }
        }

        return ret;
    }
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (!root)
            return 0;

        queue<TreeNode*> que;
        que.push(root);
        int ret = root->val;
        TreeNode *cur, *prevLast = root, *last;
        while (!que.empty()) {
            cur = que.front();
            que.pop();

            if (cur->left) {
                last = cur->left;
                que.push(cur->left);
            }
            if (cur->right) {
                last = cur->right;
                que.push(cur->right);
            }

            if (cur == prevLast) {
                prevLast = last;
                ret = !que.empty() ? que.front()->val : ret;
            }
        }

        return ret;
    }
};