/* Medium
Given a binary tree

struct Node {
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node.
If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
Example:

Given the following perfect binary tree,

     1
   /  \
  2    3
 / \  / \
4  5  6  7
After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL */

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
    Node* connect(Node* root) {
        if (!root)
            return root;

        queue<Node*> que;
        que.push(root);
        Node *cur, *last, *prev_next = root;

        while (!que.empty()) {
            cur = que.front();
            que.pop();

            if (cur->left) {
                que.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                que.push(cur->right);
                last = cur->right;
            }

            if (cur == prev_next) {
                prev_next->next = nullptr;
                prev_next = last;
            } else {
                cur->next = que.front();
            }
        }

        return root;
    }
};

class Solution {
public:
    Node* connect(Node *root) {
        if(!root)
            return root;

        if (root->left) {
            root->left->next = root->right;
            if(root->next){
                root->right->next = root->next->left;
            }
        }

        connect(root->left);
        connect(root->right);

        return root;
    }
};