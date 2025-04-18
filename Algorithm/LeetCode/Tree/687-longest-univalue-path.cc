/* Medium
Given a binary tree, find the length of the longest path where each node in the
path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:
Input:
      5
    /  \
    4   5
   / \   \
  1   1   5
Output: 2 [5-5-5]

Example 2:
Input:
      1
    /  \
   4    5
  / \   \
 4   4   5
Output: 2 [4-4-4]

Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000
The depth of the tree will not exceed 1000.

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

#include <algorithm>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        dfs(root);
        return maxLen;
    }

private:
    int dfs(TreeNode* root) {
        if (!root) {
            return 0;
        }

        const int val = root->val;
        int lft = dfs(root->left);
        int rht = dfs(root->right);

        lft = cmp(root, root->left) ? lft + 1 : 0;
        rht = cmp(root, root->right) ? rht + 1 : 0;

        maxLen = max(maxLen, lft + rht);

        return max(lft, rht);
    }

private:
    bool cmp(TreeNode* lhs, TreeNode* rhs) {
        if (!lhs || !rhs) {
            return false;
        }

        return (lhs->val == rhs->val);
    }

    // bool operator==(const TreeNode* lhs, const TreeNode* rhs) const {
    //     if (lhs || rhs) {
    //         return false;
    //     }

    //     return (lhs->val == rhs->val);
    // }


private:
    int maxLen = 0;
};

class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        if (!root)
            return 0;

        dfs(root, root->val);

        return pathMax;
    }

private:
    int dfs(TreeNode *node, int parentVal) {
        if (!node)
            return 0;

        int left = dfs(node->left, node->val);
        int right = dfs(node->right, node->val);
        pathMax = max(pathMax, left + right);

        if (node->val == parentVal)
            return max(left, right) + 1;
        else
            return 0;
    }

private:
    int pathMax{INT_MIN};
};

class Solution_ {
public:
    int path(TreeNode *root, int &pathMax) {
        if (!root || !root->left && !root->right) return 0;

        int left = path(root->left, pathMax);
        int right = path(root->right, pathMax);

        int val = root->val;
        int l = 0, r = 0;
        if (root->left && root->left->val == val) {
            l = left + 1;
        }
        if (root->right && root->right->val == val) {
            r = right + 1;
        }

        int pathBranch = max(l, r);
        if (root->left && root->right && root->left->val == val && root->right->val == val) {
            pathMax = max(pathMax, left + right + 2);
        } else {
             pathMax = max(pathMax, pathBranch);
        }

        return pathBranch;
    }

    int longestUnivaluePath(TreeNode* root) {
        int pathMax = INT_MIN;
        path(root, pathMax);

        return max(pathMax, 0);
    }
};