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
#include <sstream>
#include <iterator>

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
        dfs(root);

        return Result;
    }

private:
    void dfs(TreeNode* node) {
        if (!node)
            return;

        Path.push_back(node->val);

        if (!node->left && !node->right) {
            Result.push_back(to_path());
        } else {
            dfs(node->left);
            dfs(node->right);
        }

        // if (!Path.empty())
            Path.pop_back();
    }

    string to_path() {
        ostringstream oss;

        for (auto ite = Path.cbegin(); ite < Path.cend() - 1; ++ite) {
            oss << *ite;
            oss << "->";
        }

        if (!Path.empty())
            oss << Path.back();

        // return std::move(oss.str()); // str() returns a copy of the underlying string, no need std::move
        return oss.str();
    }

private:
    deque<int> Path;
    vector<string> Result;
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

        traverse(root);

        return result;
    }

private:
    void traverse(TreeNode* root) {
        if (!root)
            return;

        if (pathQue.empty())
           pathQue.emplace_back(to_string(root->val));
        else
            pathQue.emplace_back("->" + to_string(root->val));

        if (!root->left && !root->right) {
            std::ostringstream oss;
            std::copy(pathQue.begin(), pathQue.end(), std::ostream_iterator<string>(oss));
            result.emplace_back(oss.str());
        } else {
            traverse(root->left);
            traverse(root->right);
        }

        if (!pathQue.empty())
            pathQue.pop_back();
    }

private:
    deque<string> pathQue;
    vector<string> result;
};