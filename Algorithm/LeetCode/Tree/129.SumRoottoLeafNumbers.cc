/* Medium
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

Example:
Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.

Example 2:
Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.

Constraints:
The number of nodes in the tree is in the range [1, 3 * 10^4].
-1000 <= Node.val <= 1000

Relatives:
053. Maximum Subarray
112. Path Sum
113. Path Sum II
437. Path Sum III
666. Path Sum IV
124. Binary Tree Maximum Path Sum
129. Sum Root to Leaf Numbers
687. Longest Univalue Path
1376. Time Needed to Inform All Employees */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    int sumNumbers(TreeNode* root) {
        result = 0;

        dfs(root, 0);

        return result;
    }

private:
    void dfs(TreeNode *node, int sumCur) {
        if (!node) {
            return;
        }

        sumCur = sumCur * 10 + node->val;

        if (!node->left && !node->right) {
            result += sumCur;
        } else {
            dfs(node->left, sumCur);
            dfs(node->right, sumCur);
        }
    }

private:
    int result{0};
};