/* Easy
Given a non-empty special binary tree consisting of nodes with the non-negative
value, where each node in this tree has exactly two or zero sub-node. If the node
has two sub-nodes, then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set
made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input:
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.

Example 2:
Input:
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.

Constraints:
The number of nodes in the tree is in the range [1, 25].
1 <= Node.val <= 2^31 - 1
root.val == min(root.left.val, root.right.val) for each internal node of the tree.

Note: not a binary search tree */

#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        return secondMin(root, root->val);
    }

private:
    int secondMin(TreeNode* node, int firstMin) {
        if (!node)
            return -1;
        if (node->val != firstMin)
            return node->val;

        int left = secondMin(node->left, firstMin);
        int right = secondMin(node->right, firstMin);

        // if all nodes of a subtree = root->val,
        // there is no second minimum value, return -1
        if (left == -1)
            return right;
        else if (right == -1)
            return left;
        else
            return std::min(left, right);
    }
};

class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (!root || !root->left) return -1;

        int min = root->val;
        long min_second = LONG_MAX;
        queue<TreeNode *> que;
        que.push(root->left);
        que.push(root->right);
        TreeNode *cur = NULL;
        while (!que.empty()) {
            cur = que.front();
            que.pop();
            if (cur->val != min && cur->val < min_second)
                min_second = cur->val;
            if (cur->left)
                que.push(cur->left);
            if (cur->right)
                que.push(cur->right);
        }
        if (min < min_second && min_second != LONG_MAX)
            return min_second;
        return -1;
    }
};