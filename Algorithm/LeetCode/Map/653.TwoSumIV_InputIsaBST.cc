/* Easy
Given a Binary Search Tree and a target number, return true if there exist two
elements in the BST such that their sum is equal to the given target.

Example 1:
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9
Output: True

Example 2:
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28
Output: False

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
-10^4 <= Node.val <= 10^4
root is guaranteed to be a valid binary search tree.
-10^5 <= k <= 10^5

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include <set>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* Approach: hash set */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root)
            return false;

        if (hashSet.find(k - root->val) != hashSet.end())
            return true;

        hashSet.insert(root->val);

        return findTarget(root->left, k) || findTarget(root->right, k);
    }

private:
    std::set<int> hashSet;
};

/* Approach: inorder and two pointers */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        const auto vec = inorder(root);
        int i = 0, j = vec.size() - 1;

        while (i < j) {
            if (vec[i] + vec[j] == k)
                return true;
            else if (vec[i] + vec[j] < k)
                ++i;
            else
                --j;
        }

        return false;
    }

private:
    vector<int> inorder(TreeNode* root) {
        vector<int> vec;
        stack<TreeNode *> stk;
        TreeNode *cur = root;

        while (!stk.empty() || cur) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top()->right;
                vec.push_back(stk.top()->val);
                stk.pop();
            }
        }

        return vec;
    }
};