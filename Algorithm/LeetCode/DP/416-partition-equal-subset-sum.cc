/* Medium
Given a non-empty array nums containing only positive integers,
find if the array can be partitioned into two subsets
such that the sum of elements in both subsets is equal.

Example 1:
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 100

Relatives:
416. Partition Equal Subset Sum
698. Partition to K Equal Sum Subsets
1981. Minimize the Difference Between Target and Chosen Elements
2025. Maximum Number of Ways to Partition an Array
2035. Partition Array Into Two Arrays to Minimize Sum Difference */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % 2 != 0)
            return false;

        sum /= 2;
        const auto size = nums.size();
        vector<vector<bool>> dp(size + 1, vector(sum + 1, false));

        for (auto i = 0; i <= size; ++i) {
            dp[i][0] = true;
        }

        for (auto i = 1; i <= size; ++i) {
            for (auto j = 1; j <= sum; ++j) {
                if (j - nums[i-1] < 0) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = dp[i-1][j - nums[i-1]] || dp[i-1][j];
                }
            }
        }

        return dp[size][sum];
    }
};