/**
 * mplement an iterator over a binary search tree (BST).
 * Your iterator will be initialized with the root node of a BST.
 * Calling next() will return the next smallest number in the BST.
 * Note: next() and hasNext() should run in average O(1) time and uses O(h)
 * memory, where h is the height of the tree.
 */


/**
* Definition for binary tree
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
class BSTIterator {
private:
    vector<int> smVec;
    int index;
public:
    BSTIterator(TreeNode *root) {
        stack<TreeNode *> stk;
        index = 0;
        TreeNode *cur = root;
        while (!stk.empty() || cur) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                smVec.push_back(stk.top()->val);
                cur = stk.top()->right;
                stk.pop();
            }
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return index < smVec.size();
    }

    /** @return the next smallest number */
    int next() {
        return smVec[index++];
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
