/* Medium
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children.

Populate each next pointer to point to its next right node.
If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

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
4->5->6->7 -> NULL

Constraints:
The number of nodes in the tree is in the range [0, 2^12 - 1].
-1000 <= Node.val <= 1000

Relatives:
116. Populating Next Right Pointers in Each Node
117. Populating Next Right Pointers in Each Node II
199. Binary Tree Right Side View */

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
    Node* connect(Node* root) {
        if (!root)
            return nullptr;

        queue<Node*> que;
        que.emplace(root);
        auto* cur = root;

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

class Solution {
public:
    Node* connect(Node *root) {
        if(!root)
            return root;

        if (root->left) {
            root->left->next = root->right;
            if (root->next) {
                root->right->next = root->next->left;
            }
        }

        connect(root->left);
        connect(root->right);

        return root;
    }
};

class Solution {
public:
    Node* connect(Node *root) {
        if(!root)
            return root;

        connect(root->left, root->right);

        return root;
    }

private:
   void connect(Node* lhs, Node* rhs) {
        if (!lhs || !rhs)
            return;

        lhs->next = rhs;

        connect(lhs->left, lhs->right);
        connect(rhs->left, rhs->right);
        connect(lhs->right, rhs->left);
    }
};