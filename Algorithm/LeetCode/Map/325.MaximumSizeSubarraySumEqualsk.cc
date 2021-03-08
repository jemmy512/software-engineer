/* Medium
Given an array nums (may be negative) and a target value k, find the maximum length of a subarray that sums to k.
If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Input: nums = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.

Example 2:
Input: nums = [-2, -1, 2, 1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
Follow Up:
Can you do it in O(n) time?

Relatives:
053. Maximum Subarray
209. Minimum Size Subarray Sum
325. Maximum Size Subarray Sum Equals k
523. Continuous Subarray Sum
560. Subarray Sum Equals K */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;
        hashMap[0] = -1;  // sum == k
        int sum = 0;
        int cnt = 0;
        int maxLen = INT_MIN;

        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];

            if (hashMap.find(sum-k) != hashMap.end()) {
                maxLen = max(maxLen, i - hashMap[sum-k]);
            }

            if (hashMap.find(sum) == hashMap.end()) {
                hashMap[sum] = i;
            }
        }

        return maxLen == INT_MIN ? 0 : maxLen;
    }
};