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
*/

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
        if (!root)  return ;
        Node *cur, *next, *node = root;

        while (node) {
            cur = node;
            node = next = nullptr;
            while (cur) {
                if (cur->left){
                    if (next)
                        next = next->next = cur->left;
                    else
                        node = next = cur->left;
                }
                if (cur->right){
                    if (next)
                        next = next->next = cur->right;
                    else
                        node = next= cur->right;
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
            return;

        queue<Node*> que;
        auto* cur = root, *levelEnd = root, *last = root;
        que.emplace(root);

        while (!que.empty()) {
            cur = que.front();
            que.pop();


            if (cur->left) {
                last = cur->left;
                que.emplace(cur->left);
            }

            if (cur->right) {
                last = cur->right;
                que.emplace(cur->right);
            }

            if (cur == levelEnd) {
                levelEnd = last;
                cur->next = nullptr;
            } else {
                cur->next = que.empty() ? nullptr : que.front();
            }
        }

        return root;
    }
};
