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
#include <algorithm>
#include <iterator>

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

// Recursive Version
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, preorder.begin(), preorder.end(), inorder, inorder.begin(), inorder.end());
    }

private:
    template<typename Iter>
    TreeNode* build(vector<int>& preorder, Iter preBeg, Iter preEnd, vector<int>& inorder, Iter inBeg, Iter inEnd) {
        if (preBeg >= preEnd)
            return nullptr;

        const auto rootIter = std::find_if(inBeg, inEnd, [val = *preBeg](const auto& num) {
            return num == val;
        });
        const auto leftSize = std::distance(inBeg, rootIter);

        auto* root = new TreeNode(*preBeg);
        root->left = build(preorder, preBeg + 1, preBeg + leftSize + 1, inorder, inBeg, rootIter);
        root->right = build(preorder, preBeg + leftSize + 1, preEnd, inorder, rootIter + 1, inEnd);

        return root;
    }
};