/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
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
 
// Iterative Version
class Solution {
 public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    assert(preorder.size() == inorder.size());
    if (preorder.size() == 0) return nullptr;

    TreeNode* root;
    TreeNode** curr = &root;
    auto j = preorder.cbegin();
    stack<TreeNode*> s;
    for (auto i=inorder.cbegin(); i!=inorder.cend(); ++i) {
      while (s.empty() || s.top()->val != *i) {
        auto node = new TreeNode{*j++};
        s.push(node);
        *curr = node;
        curr = &node->left;
      }
      curr = &(s.top()->right);
      s.pop();
    }

    assert(j == preorder.cend());
    return root;
  }
};
 
// Recursive Version
class Solution_ {
public:
    TreeNode *buildTree(vector<int>& preorder, int& preidx, vector<int>& inorder) {

        if (preorder.size()<=0 || inorder.size()<=0 ) return NULL;

        TreeNode *root = new TreeNode(preorder[preidx]);
        if (inorder.size()==1){
            return root;
        }

        int i;
        for(i=0; i<inorder.size(); i++){
            if (inorder[i] == preorder[preidx]){
                break;
            }
        }

        //error: not found
        if (i == inorder.size()) return NULL;

        if (preidx+1 >= preorder.size()){
            return root;
        }

        vector<int> v(inorder.begin(), inorder.begin()+i);
        if (v.size()>0) {
            preidx++;
            root->left = buildTree(preorder, preidx, v);
        }

        v.clear();
        v.assign(inorder.begin()+i+1, inorder.end());
        if (v.size()>0) {
            preidx++;
            root->right = buildTree(preorder, preidx, v);
        }

        return root;
    }
    
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int preidx=0;
        return buildTree(preorder, preidx, inorder);
    }
};