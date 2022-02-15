/* Medium
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go
downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

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

#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* Prefix Sum
 * Complexity: O(N) */
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        _Sum = sum;

        dfs(root, 0);

        return _Cnt;
    }

private:
    void dfs(TreeNode* node, int curSum) {
        if (!node)
            return;

        curSum += node->val;

        /* case 1: curSum == _Sum */
        _Cnt += curSum == _Sum ? 1 : 0;
        /* case 2: curSum + x == _Sum */
        /* can't reorder following two lines: _Sum may 0, so curSum-_Sum == curSum */
        _Cnt += _HashMap[curSum-_Sum];

        ++_HashMap[curSum];

        dfs(node->left, curSum);
        dfs(node->right, curSum);

        --_HashMap[curSum];
    }

private:
    int _Cnt{0};
    int _Sum{0};
    unordered_map<int, int> _HashMap;
};

class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if (!root)
            return 0;

        return dfs(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }

private:
    int dfs(TreeNode *root, int curSum) {
        if (!root)
            return 0;

        curSum -= root->val;

        return (curSum == 0) + dfs(root->left, curSum) + dfs(root->right, curSum);
    }
};
