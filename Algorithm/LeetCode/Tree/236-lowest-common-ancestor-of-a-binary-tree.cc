/* Medium
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes v and w as the lowest node in T that has both v and w as
 descendants (where we allow a node to be a descendant of itself).”

Given the following binary search tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4

Example 1:
Input: root, p = 5, q = 1
Output: 3
Explanation: The LCA of of nodes 5 and 1 is 3.

Example 2:
Input: root, p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of
itself according to the LCA definition.

Constraints:
The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q
p and q will exist in the BST.

Relatives:
235.  Lowest Common Ancestor of a Binary Search Tree
236.  Lowest Common Ancestor of a Binary Tree
1644. Lowest Common Ancestor of a Binary Tree II
1650. Lowest Common Ancestor of a Binary Tree III
1676. Lowest Common Ancestor of a Binary Tree IV
1123. Lowest Common Ancestor of Deepest Leaves
1257. Smallest Common Region */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        /* left == NULL means both 'p' and 'q' are not in the left tree;
         * (left && right) means 'p' and 'q' are seperated in the left and right tree */
        return !left ? right : (!right ? left : root);
    }
};

class Solution_ {
public:
    bool findPath(TreeNode *root, TreeNode *p, vector<TreeNode *> &vec) {
        if (!root) return false;
        if (root == p) {
            vec.push_back(root);
            return true;
        }

        vec.push_back(root);
        if (findPath(root->left, p, vec)) return true;
        if (findPath(root->right, p, vec)) return true;
        vec.pop_back();

        return false;
    }

    TreeNode* lowestCommonAncestor_iter(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode *> vec1, vec2;

        if (!findPath(root, p, vec1)) return NULL;
        if (!findPath(root, q, vec2)) return NULL;

        int len = vec1.size() < vec2.size() ? vec1.size() : vec2.size();
        TreeNode *result = root;
        for (int i = 0; i < len; ++i) {
            if (vec1[i] != vec2[i]) return result;
            result = vec1[i];
        }

        return result;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lowestCommonAncestor_iter(root, p, q);
    }
};