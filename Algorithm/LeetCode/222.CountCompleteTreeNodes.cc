/*
Difficulty: Medium

Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, 
    and all nodes in the last level are as far left as possible. It can have between 
    1 and 2h nodes inclusive at the last level h.

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
*/

// 18 test cases, 81ms, beat 72.31%
class Solution {
public:
    //return -1 if it is not.
    int isCompleteTree(TreeNode* root) {
        if (!root) return 0;

        int cnt = 1;
        TreeNode *left = root, *right = root;
        for(; left && right; left = left->left, right = right->right) {
            cnt *= 2;
        }
      
        if (left!=NULL || right!=NULL) {
            return -1;
        }
        return cnt-1;
    }

    int countNodes(TreeNode* root) {
        int cnt = isCompleteTree(root);
        if (cnt != -1) return cnt;
        
        int leftCnt = countNodes(root->left);
        int rightCnt = countNodes(root->right);
        return leftCnt + rightCnt + 1;
    }
};