/*
Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

Example 1:

Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
Example 2:

Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
Example 3:

Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool isSame{false};

        if (p && q && p->val == q->val) {
            isSame = isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        } else if (q == nullptr && p == nullptr) {
            isSame = true;
        }

        return isSame;
    }
};

 // 57 test cases, 4ms, beat 80.20%
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL || q == NULL) return (p == q);
        return (p->val == q->val) &&
            isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    bool isSameTree(TreeNode *p, TreeNode *q) {
        queue<TreeNode*> q1, q2;
        q1.push(p);
        q2.push(q);
        TreeNode *p1, *p2;
        while (q1.size() > 0 && q2.size() > 0) {
            p1 = q1.front();
            p2 = q2.front();
            q1.pop();
            q2.pop();
            if (!p1 && !p2) continue;
            if (!p1 || !p2)  return false;

            if ( p1->val != p2->val)
                return false;

            q1.push(p1->left);
            q1.push(p1->right);
            q2.push(p2->left);
            q2.push(p2->right);
        }

        return true;
    }
};