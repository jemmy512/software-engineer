/* Medium
If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.

For each integer in this list:
The hundreds digit represents the depth D of this node, 1 <= D <= 4.

The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8.
The position is the same as that in a full binary tree.

The units digit represents the value V of this node, 0 <= V <= 9.

Given a list of ascending three-digits integers representing a binary tree with the depth smaller than 5,
you need to return the sum of all paths from the root towards the leaves.

It's guaranteed that the given list represents a valid connected binary tree.

Example 1:
Input: [113, 215, 221]
Output: 12
Explanation:
The tree that the list represents is:
    3
   / \
  5   1

The path sum is (3 + 5) + (3 + 1) = 12.

Example 2:
Input: [113, 221]
Output: 4
Explanation:
The tree that the list represents is:
    3
     \
      1
The path sum is (3 + 1) = 4.

Constraints:
1 <= nums.length <= 15
110 <= nums[i] <= 489
nums represents a valid binary tree with depth less than 5.

Relatives:
053. Maximum Subarray
112. Path Sum
113. Path Sum II
437. Path Sum III
666. Path Sum IV
124. Binary Tree Maximum Path Sum
129. Sum Root to Leaf Numbers
687. Longest Univalue Path
1376. Time Needed to Inform All Employees */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int pathSum(vector<int>& nums) {
        _HashMap.reserve(nums.size());

        for (const auto& num : nums) {
            _HashMap[num/10] = num % 10;
        }

        dfs(nums[0]/10, 0);

        return _Sum;
    }

private:
    void dfs(int node, int curSum) {
        if (!_HashMap.contains(node))
            return;

        curSum += _HashMap[node];

        int depth = node / 10;
        int pos = node % 10;
        int left = 10 * (depth + 1) + 2 * pos - 1;
        int right = left + 1;

        if (!_HashMap.contains(left) && !_HashMap.contains(right)) {
            _Sum += curSum;
        } else {
            dfs(left, curSum);
            dfs(right, curSum);
        }
    }

private:
    int _Sum{0};
    unordered_map<int, int> _HashMap;
};