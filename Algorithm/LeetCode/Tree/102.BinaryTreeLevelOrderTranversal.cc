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
*/

#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root)
            return {};

        vector<int> row;
        vector<vector<int>> vvec;
        queue<TreeNode*> que;
        TreeNode* cur, *preLast = root, *last;

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

            if (cur == preLast) {
                vvec.emplace_back(row);
                row.clear();
                preLast = last;
            }
        }

        return vvec;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> vvec;
        if (!root) return vvec;

        deque<TreeNode *> stk;
        deque<TreeNode *> stkk;
        stk.push_back(root);
        TreeNodeleft, *right;
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
            if (!vec.empty()) vvec.push_back(vec);
            if (!vc.empty()) vvec.push_back(vc);
        }
        return vvec;
    }
};