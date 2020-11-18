/**
 * Implement an iterator over a binary search tree (BST).
 * Your iterator will be initialized with the root node of a BST.
 * Calling next() will return the next smallest number in the BST.
 * Note: next() and hasNext() should run in average O(1) time and uses O(h)
 * memory, where h is the height of the tree.
 */

#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        inorderIterate(root);
    }

    bool hasNext() {
        return index < sortedData.size();
    }

    int next() {
        return sortedData[index++];
    }

private:
    void inorderIterate(TreeNode* node) {
        if (node == nullptr)
            return;

        inorderIterate(node->left);
        sortedData.emplace_back(node->val);
        inorderIterate(node->right);
    }

private:
    int index{0};
    std::vector<int> sortedData;
};

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        std::stack<TreeNode*> stk;
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

    bool hasNext() {
        return index < smVec.size();
    }

    int next() {
        return smVec[index++];
    }

private:
    std::vector<int> smVec;
    int index;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
