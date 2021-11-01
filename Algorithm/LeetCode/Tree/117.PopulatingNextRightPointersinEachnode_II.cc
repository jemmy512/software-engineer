/* Medium
Given a binary tree

Populate each next pointer to point to its next right node.
If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:
You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.

Example:
Given the following binary tree,

     1
   /  \
  2    3
 / \    \
4   5    7
After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL

Constraints:
The number of nodes in the tree is in the range [0, 6000].
-100 <= Node.val <= 100


Follow-up:
You may only use constant extra space.
The recursive approach is fine. You may assume implicit stack space does not count as extra space for this problem. */

#include <queue>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node *root) {
        if (!root)
            return nullptr;

        Node *cur, *next, *levelBeg = root;

        while (levelBeg) {
            cur = levelBeg;
            levelBeg = next = nullptr;
            while (cur) {
                if (cur->left){
                    if (next)
                        next = next->next = cur->left;
                    else
                        levelBeg = next = cur->left;
                }
                if (cur->right){
                    if (next)
                        next = next->next = cur->right;
                    else
                        levelBeg = next = cur->right;
                }
                cur = cur->next;
            }
        }

        return root;
    }
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root)
            return nullptr;

        queue<Node*> que;
        auto* cur = root;
        que.emplace(root);

        while (!que.empty()) {
            auto size = que.size();

            while (size--) {
                cur = que.front();
                que.pop();

                if (cur->left) {
                    que.emplace(cur->left);
                }
                if (cur->right) {
                    que.emplace(cur->right);
                }

                cur->next = que.empty() ? nullptr : que.front();
            }

            cur->next = nullptr;
        }

        return root;
    }
};
