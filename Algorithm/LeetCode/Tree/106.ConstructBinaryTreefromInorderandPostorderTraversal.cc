/* Medium
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
   15   7 */

#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Iterative Vesion
class Solution {
 public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || postorder.empty() || inorder.size() != postorder.size())
            return nullptr;

        TreeNode* root;
        TreeNode** cur = &root;
        auto postIter = postorder.crbegin();
        stack<TreeNode*> stk;

        for_each (inorder.crbegin(), inorder.crend(), [&](const auto& inVal) {
            while (stk.empty() || stk.top()->val != inVal) {
                auto* node = new TreeNode{*postIter++};
                stk.push(node);
                *cur = node;
                cur = &node->right;
            }
            cur = &(stk.top()->left);
            stk.pop();
        });

        return root;
    }
};

// Recursive Version
class Solution {
public:
    TreeNode *buildTree(vector<int>& inorder, vector<int>& post) {
        return build(inorder, inorder.rbegin(), inorder.rend(), post, post.rbegin(), post.rend());
    }

private:
    template<typename Iter>
    TreeNode* build(const vector<int>& inorder, Iter inBeg, Iter inEnd, const vector<int>& postorder, Iter postBeg, Iter postEnd) {
        if (postBeg >= postEnd)
            return nullptr;

        const auto rootIter = std::find_if(inBeg, inEnd, [postBeg](const auto& val) {
            return val == *postBeg;
        });
        const auto rightSize = std::distance(inBeg, rootIter);

        auto* node = new TreeNode(*postBeg);
        node->right = build(inorder, inBeg, rootIter, postorder, postBeg + 1, postBeg + rightSize + 1);
        node->left = build(inorder, rootIter + 1, inEnd, postorder, postBeg + rightSize + 1, postEnd);

        return node;
    }
};