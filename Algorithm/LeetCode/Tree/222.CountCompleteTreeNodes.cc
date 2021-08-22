/* Medium
Given a complete binary tree, count the number of nodes.

Note:
Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled,
and all nodes in the last level are as far left as possible. 
It can have between 1 and 2h nodes inclusive at the last level h.

Example:
Input:
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6 */

#include <optional>

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
    std::optional<int> getCompleteTreeCnt(TreeNode* root) {
        if (!root) 
            return {};

        int cnt = 1;
        TreeNode *left = root, *right = root;
        for (; left && right; left = left->left, right = right->right) {
            cnt *= 2;
        }

        if (left || right) {
            return {};
        }
        return {cnt-1};
    }

    int countNodes(TreeNode* root) {
        if (!root)
            return 0;

        if (const auto cnt = getCompleteTreeCnt(root); cnt) {
            return cnt.value();
        }
        
        int leftCnt = countNodes(root->left);
        int rightCnt = countNodes(root->right);
        return leftCnt + rightCnt + 1;
    }
};