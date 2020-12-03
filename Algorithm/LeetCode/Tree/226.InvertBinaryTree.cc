/*
Difficulty: Easy

Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew),
but you can’t invert a binary tree on a whiteboard so f*** off.
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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;

        queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            TreeNode *node = queue.front();
            queue.pop();
            swap(node->left, node->right);
            if (node->left)
                queue.push(node->left);
            if (node->right)
                queue.push(node->right);
        }

        return root;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return root;

        std::swap(root->left, root->right);

        if (root->left)
            invertTree(root->left);
        if (root->right)
            invertTree(root->right);

        return root;
    }
};