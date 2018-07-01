/**
 * Given a binary tree, return the zigzag level order traversal of its nodes' values.
 * (ie, from left to right, then right to left for the next level and alternate between).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
   return its zigzag level order traversal as:
   [
  [3],
  [20,9],
  [15,7]
]
 */


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> vvec;
        if (!root) return vvec;

        TreeNode *pre_last = root, *cur, *last;
        queue<TreeNode *> nodes;
        vector<int> vec;
        bool zigzag = false;
        nodes.push(root);
        while (!nodes.empty()) {
            cur = nodes.front();
            vec.push_back(cur->val);

            if (cur->left) {
                nodes.push(cur->left);
                last = cur->left;
            }
            if (cur->right) {
                nodes.push(cur->right);
                last = cur->right;
            }

            if (cur == pre_last) {
                if (zigzag)
                    reverse(vec.begin(), vec.end());
                zigzag = !zigzag;
                vvec.push_back(vec);
                vec.clear();
                pre_last = last;
            }
            nodes.pop();
        }

        return vvec;
    }
};