/* Medium
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
   15   7 */

#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Iterative Version
class Solution {
 public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size())
            return nullptr;

        TreeNode* root;
        TreeNode** cur = &root;
        auto preIter = preorder.cbegin();
        stack<TreeNode*> stk;

        for (const auto& inValue : inorder) {
            while (stk.empty() || stk.top()->val != inValue) {
                auto* node = new TreeNode{*preIter++};
                stk.push(node);
                *cur = node;
                cur = &node->left;
            }
            cur = &(stk.top()->right);
            stk.pop();
        }

        return root;
    }
};

/* The idea is as follows:
1. Keep pushing the nodes from the preorder into a stack (and keep making the tree by adding nodes to the left of the
    previous node) until the top of the stack matches the inorder.
2. At this point, pop the top of the stack until the top does not equal inorder
    (keep a flag to note that you have made a pop).
3. Repeat 1 and 2 until preorder is empty. The key point is that whenever the flag is set, insert a node to the right and reset the flag. */
class Solution {
public:
    TreeNode *buildTree(vector &preorder, vector &inorder) {
        if(preorder.size()==0)
         return NULL;

        stack<int> s;
        stack<TreeNode *> st;
        TreeNode *t,*r,*root;
        int i,j,f;

        f=i=j=0;
        s.push(preorder[i]);

        root = new TreeNode(preorder[i]);
        st.push(root);
        t = root;
        i++;

        while(i<preorder.size()) {
            if(!st.empty() && st.top()->val==inorder[j]) {
                t = st.top();
                st.pop();
                s.pop();
                f = 1;
                j++;
            } else {
                if(f==0) {
                    s.push(preorder[i]);
                    t -> left = new TreeNode(preorder[i]);
                    t = t -> left;
                    st.push(t);
                    i++;
                } else {
                    f = 0;
                    s.push(preorder[i]);
                    t -> right = new TreeNode(preorder[i]);
                    t = t -> right;
                    st.push(t);
                    i++;
                }
            }
        }

        return root;
    }
};

// Recursive Version
class Solution {
public:
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int& p, int& i, int end) {
        if(i < inorder.size() && (end == inorder.size() || inorder[i] != preorder[end])) {
            TreeNode* ret = new TreeNode(preorder[p++]);
            ret->left = dfs(preorder, inorder, p, i, p-1);
            ++i;
            ret->right = dfs(preorder, inorder, p, i, end);
            return ret;
        } else
            return NULL;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int p = 0, i = 0;
        int end = inorder.size();
        return dfs(preorder, inorder, p, i, end);
    }
};

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