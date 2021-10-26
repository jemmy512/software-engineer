/* Medium
Given a binary tree, return the level order traversal of its nodes' values.
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

Relatives:
102. Binary Tree Level Order Traversal
104. Maximum Depth of Binary Tree
111. Minimum Depth of Binary Tree
752. Open the Lock */

#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// recursion
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return rows;

        levelOrder(root, 0);

        return rows;
    }

private:
    void levelOrder(TreeNode* node, int level) {
        if (rows.size() == level)
            rows.push_back({});

        rows[level].emplace_back(node->val);

        if (node->left)
            levelOrder(node->left, level+1);
        if (node->right)
            levelOrder(node->right, level+1);
    }

private:
    vector<vector<int>> rows;
};

// level loop
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};

        vector<vector<int>> rows;
        queue<TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            rows.push_back({});

            auto size = que.size();
            while (size-- > 0) {
                auto* node = que.front();
                que.pop();
                rows.back().emplace_back(node->val);

                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
        }

        return rows;
    }
};

// sentinal
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};

        vector<int> row;
        vector<vector<int>> rows;
        queue<TreeNode*> que;
        TreeNode* cur, *levelEnd = root, *last;

        que.push(root);
        while (!que.empty()) {
            cur = que.front(); que.pop();
            row.emplace_back(cur->val);

            if (cur->left) {
                que.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                que.push(cur->right);
                last = cur->right;
            }

            if (cur == levelEnd) {
                rows.emplace_back(row);
                row.clear();
                levelEnd = last;
            }
        }

        return rows;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> rows;
        deque<TreeNode *> stk;
        deque<TreeNode *> stkk;
        stk.push_back(root);
        TreeNode* left, *right;
        while (!stk.empty() || !stkk.empty()) {
            vector<int> vec;
            while (!stk.empty()) {
                vec.push_back(stk.front()->val);
                left = stk.front()->left;
                right = stk.front()->right;
                if (left) stkk.push_back(left);
                if (right) stkk.push_back(right);
                stk.pop_front();
            }
            vector<int> vc;
            while (!stkk.empty()) {
                vc.push_back(stkk.front()->val);
                left = stkk.front()->left;
                right = stkk.front()->right;
                if (left) stk.push_back(left);
                if (right) stk.push_back(right);
                stkk.pop_front();
            }
            if (!vec.empty()) rows.push_back(vec);
            if (!vc.empty()) rows.push_back(vc);
        }
        return rows;
    }
};