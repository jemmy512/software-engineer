/* Easy
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24. */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void leftCount(TreeNode *root, bool isLeft, int& ret) {
        if (!root)
            return;

        if (isLeft && !root->left && !root->right) {
            ret += root->val;
        }

        leftCount(root->left, true, ret);
        leftCount(root->right, false, ret);
    }

    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;

        int ret = 0;
        leftCount(root, 0, ret);

        return ret;
    }
};