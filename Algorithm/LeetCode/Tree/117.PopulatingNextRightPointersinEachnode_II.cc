/*
Given a binary tree

struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next
    right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space 
    for this problem.
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

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
 
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root)  return ;
        TreeLinkNode *cur, *left;
        while(root){
            cur = root;
            root = left = nullptr;
            while(cur){
                if (cur->left){
                    if (left) left = left->next = cur->left;
                    else  root = left = cur->left;
                }
                if (cur->right){
                    if (left) left = left->next = cur->right;
                    else root = left= cur->right;
                }
                cur = cur->next;
            }
        }
    }
};
 
class Solution_ {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        
        queue<TreeLinkNode *> que;
        TreeLinkNode *cur, *next, *prev_next = root;
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
