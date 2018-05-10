/*
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most 
    frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the 
    implicit stack space incurred due to recursion does not count).
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
class Solution {
public:
    void handleValue(int val) {
        if (val != currVal) {
            currVal = val;
            currCount = 0;
        }
        
        ++currCount;
        if (currCount > maxCount) {
            maxCount = currCount;
            modeCount = 1;
        } else if (currCount == maxCount) {
             if (!vec.empty())
                vec[modeCount] = currVal;
            ++modeCount;
        }
    }
    
    void morrisInOrder(TreeNode *root) {
        TreeNode *node = root, *prev = NULL;
        while (node) {
            if (node->left == NULL) {
                handleValue(node->val);
                node = node->right;
            } else {
                prev = node->left;
                while (prev->right && prev->right != node)
                    prev = prev->right;
                
                if (prev->right) {
                    prev->right = NULL;
                    handleValue(node->val);
                    node = node->right;
                } else {
                    prev->right = node;
                    node = node->left;
                }
            }
        }
    }
    
    vector<int> findMode(TreeNode* root) {
        morrisInOrder(root);
        vec.resize(modeCount, 0);
        modeCount = 0;
        currCount = 0;
        morrisInOrder(root);
        
        return vec;
    }
private:
    int currVal;
    int currCount = 0;
    int maxCount = 0;
    int modeCount = 0;
    vector<int> vec;
};

vector<int> vec = {6,2,1,4,3,5,7,9,8};
    TreeNode *root = NULL;
    for (int i : vec) {
        root = insertNode(root, i);
    }

// [20,10,30,5,15,25,40,null,null,null,null,null,30]