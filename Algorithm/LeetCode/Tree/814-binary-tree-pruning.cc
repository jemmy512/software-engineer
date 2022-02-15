/* Medium
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

Example 1:
Input: [1,nullptr,0,0,1]
Output: [1,nullptr,0,nullptr,1]

Explanation:
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.
 1          1
  \          \
   0  --->    0
  / \          1
 0   1


Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,nullptr,1,nullptr,1]
     1            1
   /   \           \
  0     1   -->     1
 / \   / \           \
0   0 0   1           1

Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,nullptr,1]

         1                1
       /   \            /  \
      1     0   -->    1    0
     / \   / \        / \    \
    1   1 0   1      1   1    1
   /
  0

Note:
The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1. */

#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        /* the root could be deleted */
        TreeNode dummyNode{};
        dummyNode.left = root;
        prune(&dummyNode);

        return dummyNode.left;
    }

private:
    bool prune(TreeNode* root) {
        if (!root)
            return false;

        bool left = prune(root->left);
        bool right = prune(root->right);

        if (!left) {
            delete root->left; // delete nullptr has no effect
            root->left = nullptr;
        }
        if (!right) {
            delete root->right;
            root->right = nullptr;
        }

        return (root->val || left || right);
    }
};