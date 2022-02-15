/* Medium
Given a list of non-negative numbers and a target integer k, write a function to
check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is,
sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.

Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.

Note:
The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

Constraints:
1 <= nums.length <= 10^5
0 <= nums[i] <= 10^9
0 <= sum(nums[i]) <= 2^31 - 1
1 <= k <= 2^31 - 1

Realtives:
053. Maximum Subarray
209. Minimum Size Subarray Sum
325. Maximum Size Subarray Sum Equals k
523. Continuous Subarray Sum
560. Subarray Sum Equals K

0516. Longest Palindromic Subsequence
1682. Longest Palindromic Subsequence II
1062. Longest Repeating Substring
1092. Shortest Common Supersequence
1143. Longest Common Subsequence */

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int sum = 0;
        unordered_map<int, int> hashMap;
        hashMap.reserve(nums.size());
        hashMap.emplace(0, -1);

        for (int i = 0; i < nums.size(); ++i) {
            sum = (sum + nums[i]) % k;
            if (hashMap.contains(sum)) {
                if (i - hashMap[sum] > 1)
                    return true;
            } else {
                hashMap.emplace(sum, i);
            }
        }

        return false;
    }
};

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int sum = 0, pre = 0;
        unordered_set<int> modk;

        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            int mod = (k == 0 ? sum : sum % k);
            if (modk.find(mod) != modk.end())
                return true;
            modk.insert(pre);
            pre = mod;
        }

        return false;
    }
};

class Solution_ { // Doesn't work
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int len  = nums.size();
        if (len < 2) return false;

        int sumMax = nums[0];
        int sumCur = nums[0];
        int beg = 0, end = 0;
        for (int i = 1; i < len; ++i, ++end) {
            if (nums[i] >= sumCur + nums[i])
                beg = i;
            sumCur = max(nums[i], sumCur += nums[i]);
            sumMax = max(sumMax, sumCur);
            if (k == 0) {
                if (sumMax == 0) return true;
                return false;
            } else {
                int tempSum = sumMax;
                int j = beg;
                while (tempSum >= k || sumMax == 0) {
                    if (tempSum % k == 0) return true;
                    tempSum -= nums[j++];
                }
            }
        }

        return false;
    }
};