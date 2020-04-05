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
    assert(inorder.size() == postorder.size());
    if (inorder.size() == 0) return nullptr;

    TreeNode* root;
    TreeNode** curr = &root;
    auto j = postorder.crbegin();
    stack<TreeNode*> s;
    for (auto i=inorder.crbegin(); i!=inorder.crend(); ++i) {
      while (s.empty() || s.top()->val != *i) {
        auto node = new TreeNode{*j++};
        s.push(node);
        *curr = node;
        curr = &node->right;
      }
      curr = &(s.top()->left);
      s.pop();
    }

    assert(j == postorder.crend());
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