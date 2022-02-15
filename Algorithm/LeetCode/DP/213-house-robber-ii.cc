/* Medium
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed. All houses at this place are arranged in a circle.
That means the first house is the neighbor of the last one.
Meanwhile, adjacent houses have a security system connected,
and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house,
return the maximum amount of money you can rob tonight without alerting the police.

Example 1:
Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:
Input: nums = [1,2,3]
Output: 3

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 1000

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

#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        const auto size = nums.size();
        if (size == 1)
            return nums[0];

        return max(robRange(nums, 0, size - 1), robRange(nums, 1, size));
    }

private:
    int robRange(const vector<int>& nums, int beg, int end) {
        int dp_i_2 = 0;
        int dp_i_1 = 0;

        for (auto i = beg; i < end; ++i) {
            auto cur = max(dp_i_1, dp_i_2 + nums[i]);
            dp_i_2 = dp_i_1;
            dp_i_1 = cur;
        }

        return dp_i_1;
    }
};