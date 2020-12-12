/* Medium
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2

Example 2:

Input: nums = [1,2,3], k = 3
Output: 2

Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107

Relative:
121. Best Time to Buy and Sell Stock
152. Maximum Product Subarry
437.PathSum_III
523. Continuous Subarray Sum
560. Sub array Sum Equals K */

#include <unordered_map>
#include <vector>

using namespace std;

/* Prefix Sum, solution ref: https://leetcode.com/problems/path-sum-iii/solution/ */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;
        int curSum = 0;
        int cnt = 0;

        for (const auto& num : nums) {
            curSum += num;

            if (curSum == k)
                ++cnt;
            cnt += hashMap[curSum-k];
            ++hashMap[curSum];
        }

        return cnt;
    }
};
