/*
Difficulty: Medium

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
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
 
// Iterative Vesion
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0 || inorder.size() != postorder.size())
            return nullptr;
        
        stack<TreeNode *> stk;
        auto i = inorder.crbegin();
        auto p = postorder.crbegin();
        TreeNode *root = nullptr, **cur = &root;
        
        for (; i != inorder.crend(); ++i) {
            while (stk.empty() || stk.top()->val != *i) {
                TreeNode *node = new TreeNode(*p++);
                *cur = node;
                cur = &(node->right);
                stk.push(node);
            }
            cur = &(stk.top()->left);
            stk.pop();
        }
        
        if (p != postorder.crend()) // Case: the two orders contain different numbers
            return nullptr;
        return root;
    }
}; 
 
// Recursive Version
class Solution_ {
public:
    TreeNode *buildTree(vector<int> &inorder, int in_offset, vector<int> &postorder, int post_offset, int n ) {

        if ( n<=0 || postorder.size()<=0 || inorder.size()<=0 ) return NULL;

        TreeNode *root = new TreeNode(postorder[post_offset+n-1]);
        if ( n==1 ){
            return root;
        }

        //searching in inorder -- can be optimized by using <map>
        int i;
        for(i=in_offset; i<in_offset+n; i++){
            if (inorder[i] == postorder[post_offset+n-1])
                break;
        }

        //error: not found
        if (i == inorder.size()) return NULL;

        int left_n = i - in_offset;
        int right_n = in_offset + n - i - 1;
        root->left = buildTree(inorder, in_offset, postorder, post_offset, left_n );
        root->right = buildTree(inorder, i+1, postorder, post_offset+left_n, right_n);

        return root;
    }
    
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree(inorder, 0, postorder, 0, postorder.size());
    }
};