/* Medium
Given a binary tree

Populate each next pointer to point to its next right node. If there is no next
    right node, the next pointer should be set to NULL.

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
    void connect(Node *root) {
        if (!root)  return ;
        Node *cur, *left;

        while (root) {
            cur = root;
            root = left = nullptr;
            while (cur) {
                if (cur->left){
                    if (left)
                        left = left->next = cur->left;
                    else
                        root = left = cur->left;
                }
                if (cur->right){
                    if (left)
                        left = left->next = cur->right;
                    else
                        root = left= cur->right;
                }
                cur = cur->next;
            }
        }
    }
};

class Solution_ {
public:
    void connect(Node *root) {
        if (!root) return;

        queue<Node *> que;
        Node *cur, *next, *prev_next = root;
        que.push(root);

        while (!que.empty()) {
            cur = que.front();
            que.pop();

            if (cur->left) {
                que.push(cur->left);
                next = cur->left;
            }
            if (cur->right) {
                que.push(cur->right);
                next = cur->right;
            }

            if (cur == prev_next) {
                prev_next->next = NULL;
                prev_next = next;
            } else {
                cur->next = que.front();
            }
        }
    }
};
