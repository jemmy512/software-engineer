/*
Difficulty: Easy

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false. */

#include <cmath>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;

        bool flag = true;
        levelCount(root, flag);

        return flag;
    }

private:
    int levelCount(TreeNode* root, bool& flag) {
        if (!root)
            return 0;
        if (!flag)
            return 0;

        int ll = levelCount(root->left, flag);
        int lr = levelCount(root->right, flag);
        if (std::abs(ll - lr) > 1) {
            flag = false;
            return 0;
        }

        return 1 + max(ll, lr);
    }
};

/* Time complexity:  O(nlogn)
 *  * For a node p at depth d, height(p) will be called d times.
 *
 * Space complexity: O(n). */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if (!root)
            return true;
        return abs(height(root->left) - height(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);
    }

private:
    int height(TreeNode* node) {
        if (!node) // An empty tree has height -1
            return -1;
        return std::max(height(node->left), height(node->right)) + 1;
    }
};
