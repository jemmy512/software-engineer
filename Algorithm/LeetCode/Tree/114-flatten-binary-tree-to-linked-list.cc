/* Medium
Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:
    1
   / \
  2   5
 / \   \
3   4   6

The flattened tree should look like:
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
Hint:
    If you notice carefully in the flattened tree, each node's right child
    points to the next node of a pre-order traversal. */

#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        dfs(root);
    }

private:
    TreeNode* dfs(TreeNode* node) {
        if (!node)
            return nullptr;

        auto* leftLeaf = dfs(node->left);
        auto* rightLeaf = dfs(node->right);

        if (leftLeaf) {
            leftLeaf->right = node->right;
            node->right = node->left;
            node->left = nullptr;
        }

        if (!leftLeaf && !rightLeaf)
            return node;

        return rightLeaf ? rightLeaf : leftLeaf;
    }
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root)
            return;

        flatten(root->left);
        flatten(root->right);

        auto* left = root->left;
        auto* right = root->right;

        root->left = nullptr;
        root->right = left;

        auto* cur = root;
        while (cur->right) {
            cur = cur->right;
        }
        cur->right = right;
    }
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root)
            return;

        stack<TreeNode*> stk;
        vector<TreeNode*> vec;
        TreeNode *cur = root;

        while (!stk.empty() || cur) {
            if (cur) {
                vec.push_back(cur);
                stk.push(cur);
                cur = cur ->left;
            } else {
                cur = stk.top()->right;
                stk.pop();
            }
        }

        for (int i = 0; i < vec.size()-1; ++i) {
            vec[i]->left = NULL;
            vec[i]->right = vec[i+1];
        }
    }
};