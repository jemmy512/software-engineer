/* Medium
Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q.

If either node p or q does not exist in the tree, return null.

All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia:
"The lowest common ancestor of two nodes p and q in a binary tree
T is the lowest node that has both p and q as descendants
(where we allow a node to be a descendant of itself)".
A descendant of a node x is a node y that is on the path from node x to some leaf node.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.

Example 3:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
Output: null
Explanation: Node 10 does not exist in the tree, so return null.


Constraints:
The number of nodes in the tree is in the range [2, 10^5].
-10^9 <= Node.val <= 10^9
All Node.val are unique.
p != q

Note: p and q may not exist in the BST.

Follow up: Can you find the LCA traversing the tree, without checking nodes existence? *

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
        auto* ret = lca(root, p, q);

        return _FindCnt == 2 ? ret : nullptr;
    }

private:
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root)
            return root;

        /* won't go down if lca is p
         * p, q may be null, it needs to traverse all nodes */
        // if (root == p || root == q) {
        //     ++_FindCnt;
        //     return root;
        // }

        auto* left = lca(root->left, p, q);
        auto* right = lca(root->right, p, q);

        if (root == p || root == q) {
            ++_FindCnt;
            return root;
        }

        return !left ? right : (!right ? left : root);
    }

private:
    int _FindCnt{0};
};