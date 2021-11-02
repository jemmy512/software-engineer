/* Hard
Given a binary tree root, return the maximum sum of all keys of any sub-tree
which is also a Binary Search Tree (BST).

Assume a BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:
Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
Output: 20
Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.

Example 2:
Input: root = [4,3,null,1,2]
Output: 2
Explanation: Maximum sum in a valid Binary search tree is obtained in a single root node with key equal to 2.

Example 3:
Input: root = [-4,-2,-5]
Output: 0
Explanation: All values are negatives. Return an empty BST.

Example 4:
Input: root = [2,1,3]
Output: 6

Example 5:
Input: root = [5,4,8,3,null,6,3]
Output: 7

Constraints:
The number of nodes in the tree is in the range [1, 4 * 10^4].
-4 * 10^4 <= Node.val <= 4 * 10^4 */

#include <map>
#include <vector>

using namespace std;

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
    int maxSumBST(TreeNode* root) {
        traverse(root);
        return MaxSum;
    }

private:
    tuple<bool, int, int, int> traverse(TreeNode* node) {
        if (!node) {
            return {true, INT_MAX, INT_MIN, 0};
        }

        const auto [isBstL, minL, maxL, sumL] = traverse(node->left);
        const auto [isBstR, minR, maxR, sumR] = traverse(node->right);

        if (isBstL && isBstR && node->val > maxL && node->val < minR) {
            auto sum = node->val + sumL + sumR;
            MaxSum = max(sum, MaxSum);
            return {true, min(minL, node->val), max(maxR, node->val), sum};
        } else {
            return {false, INT_MAX, INT_MIN, 0};
        }
    }

private:
    int MaxSum{0};
};