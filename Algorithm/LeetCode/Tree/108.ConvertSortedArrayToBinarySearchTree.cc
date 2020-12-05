/* Easy
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of
the two subtrees of every node never differ by more than 1.

Example:
Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#include <vector>

using namespace std;

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return convert(nums, 0, nums.size());
    }

private:
    TreeNode* convert(const vector<int>& nums, int beg, int end) {
        if (beg >= end)
            return nullptr;

        int mid = beg + (end - beg) / 2;
        auto* node = new TreeNode(nums[mid]);
        node->left = convert(nums, beg, mid);
        node->right = convert(nums, mid+1, end);

        return node;
    }
};