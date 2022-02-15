/* Easy
Given a binary tree and a sum, determine if the tree has a root-to-leaf path
such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:
Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        return dfs(root, targetSum);
    }

private:
    bool dfs(TreeNode* node, int targetSum) {
        if (!node)
            return false;

        targetSum -= node->val;

        if (!node->left && !node->right)
            return targetSum == 0;

        return dfs(node->left, targetSum) || dfs(node->right, targetSum);
    }
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {

        if (root == NULL) return false;

        if (root->left == NULL  && root->right == NULL  ){
            return (root->val==sum);
        }

        if (root->left){
            root->left->val += root->val;
            if (hasPathSum(root->left, sum)){
                return true;
            }
        }

        if (root->right){
            root->right->val += root->val;
            if (hasPathSum(root->right, sum)){
                return true;
            }
        }

        return false;
    }
};

class Solution {
public:
    void pathSum(TreeNode *root, int curSum, int expSum, bool &flag) {
        if (!root) return;

        curSum += root->val;
        bool isLeaf = !root->left && !root->right;
        if (isLeaf && curSum == expSum) {
            flag = true;
            return;
        }

        if (root->left)
            pathSum(root->left, curSum, expSum, flag);
        if (root->right)
            pathSum(root->right, curSum, expSum, flag);
        curSum -= root->val;
    }

    bool hasPathSum(TreeNode* root, int sum) {
        bool flag = false;
        pathSum(root, 0, sum, flag);
        return flag;
    }
};