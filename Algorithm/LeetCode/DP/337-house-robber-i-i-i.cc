/* Medium
The thief has found himself a new place for his thievery again.
There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house.
After a tour, the smart thief realized that all houses in this place form a binary tree.
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

Example 1:
Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:
Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.

Constraints:
The number of nodes in the tree is in the range [1, 10^4].
0 <= Node.val <= 10^4

Relatives:
053. Maximum Subarray
121. Best Time to Buy and Sell Stock
152. Maximum Product Subarry
198. House Robber
213. House Robber II
337. House Robber III
238. Product of Array Except Self
256. Paint House
276. Paint Fence
437. Path Sum III
560. Sub array Sum Equals K
600. Non-negative Integers without Consecutive Ones
628. Maximum Product of Three Numbers
656. Coin Path
713. Subarray Product Less Than K
740. Delete and Earn */

#include <utility>
#include <algorithm>

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
    int rob(TreeNode* root) {
        const auto [doRob, dontRob] = dp(root);

        return max(doRob, dontRob);
    }

private:
    pair<int, int> dp(TreeNode* node) {
        if (!node)
            return { 0, 0 };

        const auto [robLeft, dontRobLeft] = dp(node->left);
        const auto [robRight, dontRobRight] = dp(node->right);

        const auto doRob = node->val + dontRobLeft + dontRobRight;
        const auto dontRob = max(robLeft, dontRobLeft) + max(robRight, dontRobRight);

        return { doRob, dontRob };
    }
};