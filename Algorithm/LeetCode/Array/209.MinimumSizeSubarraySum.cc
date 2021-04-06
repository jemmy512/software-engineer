/* Medium
Given an array of n positive integers and a positive integer s, find the minimal
length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:
Input: [2,3,1,2,4,3], s = 7
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Relatives:
076. Minimum Window Substring
053. Maximum Subarray
209. Minimum Size Subarray Sum
325. Maximum Size Subarray Sum Equals k
523. Continuous Subarray Sum
560. Subarray Sum Equals K
718. Maximum Length of Repeated Subarray
1658. Minimum Operations to Reduce X to Zero */

#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int beg = 0;
        int sum = 0;
        int minLen = INT_MAX;

        for (auto cur = 0; cur < nums.size(); ++cur) {
            sum += nums[cur];
            while (sum >= s) {
                minLen = min(minLen, cur-beg+1);
                sum -= nums[beg++];
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        auto len = nums.size();
        auto ans = INT_MAX;
        vector sums(len + 1, 0);

        for (auto i = 1; i <= len; i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        for (auto i = 1; i <= len; i++) {
            auto target = s + sums[i - 1];
            auto pos = lower_bound(sums.begin(), sums.end(), target);
            if (pos != sums.end()) {
                ans = min(ans, static_cast<int>(pos - (sums.begin() + i - 1)));
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }
};