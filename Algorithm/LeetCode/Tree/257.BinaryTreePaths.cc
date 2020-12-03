/* Easy
Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3 */

#include <vector>
#include <string>
#include <algorithm>
#include <stack>

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
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root)
            return {};

        vector<string> pathes;
        stack<string> pathStack;
        stack<TreeNode*> nodeStack;

        pathStack.push(to_string(root->val));
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            auto* node = nodeStack.top(); nodeStack.pop();
            auto path = pathStack.top(); pathStack.pop();

            if (!node->left && !node->right)
                pathes.emplace_back(path);

            if (node->right) {
                nodeStack.push(node->right);
                pathStack.push(path + "->" + to_string(node->right->val));
            }

            if (node->left) {
                nodeStack.push(node->left);
                pathStack.push(path + "->" + to_string(node->left->val));
            }
        }

        return pathes;
    }
};

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root)
            return {};

        vector<string> vec;
        traverse(root, vec, "");

        return vec;
    }

private:
    void traverse(TreeNode* root, vector<string>& vec, string path) {
        if (!root) return;

        if (!path.empty())
            path +=  "->";
        path += to_string(root->val);

        if (!root->left && !root->right) {
            vec.emplace_back(path);
        } else {
            traverse(root->left, vec, path);
            traverse(root->right, vec, path);
        }
    }
};