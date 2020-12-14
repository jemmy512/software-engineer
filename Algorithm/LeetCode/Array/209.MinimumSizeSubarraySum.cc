/* Medium
Given an array of n positive integers and a positive integer s, find the minimal
length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:
Input: [2,3,1,2,4,3], s = 7
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Relatives:
76. Minimum Window Substring
209. Minimum Size Subarray Sum
325. Maximum Size Subarray Sum Equals k
1658. Minimum Operations to Reduce X to Zero
718. Maximum Length of Repeated Subarray */

#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int minLen = INT_MAX;
        int beg = 0, sum = 0;

        for (int idx = 0; idx < nums.size(); ++idx) {
            sum += nums[idx];
            while (sum >= s) {
                minLen = min(minLen, idx - beg + 1);
                sum -= nums[beg++];
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

class Solution_ {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = nums.size();
        int min = len;
        bool has = false;
        int begin = 0, end = 0, sum = 0;

        for (int i = 0; i < len; ++i, ++end) {
            sum += nums[i];
            while (sum >= s && begin <= end) { // '=' fix the case: 15 [1,2,3,4,5]
                if (begin == end) return 1;
                if (end - begin + 1 <= min) {
                    has = true;
                    min = end - begin + 1;
                }
                sum -= nums[begin++];
            }
        }

        return has ? min : 0;
    }
};