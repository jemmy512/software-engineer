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

#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
            return 0;

        if (!root->left)
            return minDepth(root->right) + 1;
        else if (!root->right)
            return minDepth(root->left) + 1;
        else
            return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};