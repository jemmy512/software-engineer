/* Medium
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:

Input: nums = [1]
Output: [[1]]


Constraints:
1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.

Relatives:
078. Subsets
090. Subsets II

046. Permutations
047. Permutations II

077. Combinations
039. Combination Sum
040. Combination Sum II
216. Combination Sum III
377. Combination Sum IV */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        backtrack(nums, 0, result);

        return result;
    }

private:
    void backtrack(vector<int>& nums, int idx, vector<vector<int>>& result) {
        if (idx + 1 == nums.size()) {
            result.emplace_back(nums);
        } else {
            for (int i = idx; i < nums.size(); ++i) {
                swap(nums[idx], nums[i]);
                backtrack(nums, idx+1, result);
                swap(nums[idx], nums[i]);
            }
        }
    }

    bool isSwap(vector<int>& nums, int beg, int end) {
        for (; beg < end; ++beg) {
            if (nums[beg] == nums[end])
                return false;
        }

        return true;
    }
};