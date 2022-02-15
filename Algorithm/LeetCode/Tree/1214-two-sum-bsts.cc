/* Medium
Given two binary search trees, return True if and only if
there is a node in the first tree and a node in the second tree
whose values sum up to a given integer target.

Example 1:
Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
Output: true
Explanation: 2 and 3 sum up to 5.

Example 2:
Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
Output: false

Constraints:
Each tree has at most 5000 nodes.
-10^9 <= target, node.val <= 10^9

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include <stack>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        stack<TreeNode*> stk;
        unordered_set<int> hashSet;
        auto* cur = root1;

        while (!stk.empty() || cur) {
            if (cur) {
                stk.push(cur);
                hashSet.insert(target-cur->val);
                cur = cur->left;
            } else {
                cur = stk.top()->right;
                stk.pop();
            }
        }

        cur = root2;
        while (!stk.empty() || cur) {
            if (cur) {
                if (hashSet.find(cur->val) != hashSet.end())
                    return true;

                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top()->right;
                stk.pop();
            }
        }

        return false;
    }
};