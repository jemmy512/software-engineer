/* Medium
Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from an array
by deleting some or no elements without changing the order of the remaining elements.
For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].

Example 1:
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

Example 2:
Input: nums = [0,1,0,3,2,3]
Output: 4

Example 3:
Input: nums = [7,7,7,7,7,7,7]
Output: 1

Constraints:
1 <= nums.length <= 2500
-10^4 <= nums[i] <= 10^4

Follow up:
Could you come up with the O(n^2) solution?
Could you improve it to O(n log(n)) time complexity?

Relatives:
300. Longest Increasing Subsequence
1048. Longest String Chain */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

/* Solution 1.1
 * Solution 1.1 is the same as 1.1 except that 1.2 uses STL which is faster
 * Time Complexity: O(N^2)
 * Space Complexity: O(N) */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int maxLen = 0;
        vector<pair<int, int>> lenVec;
        lenVec.reserve(nums.size()+1);
        lenVec.emplace_back(INT_MIN, INT_MIN);

        for (int i = 0; i < nums.size(); ++i) {
            /* Pitfall: if no element statifies the requirement, max_element returns the first element
             * reutrn the end() only if the range [begin, end) is empty */
            auto pos = max_element(lenVec.cbegin(), lenVec.cend(), [&tar = nums[i]](const auto& largest, const auto& item) {
                return largest.first < tar && item.first < tar && largest.second < item.second;
            });

            auto len = pos != lenVec.cbegin() && pos != lenVec.cend() ? (pos->second + 1) : 1;
            lenVec.emplace_back(nums[i], len);
            maxLen = max(maxLen, len);
        }

        return maxLen;
    }
};

/* Solution 1.2 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int maxLen = 1;
        vector dp(nums.size(), 1);

        for (int i = 1; i < dp.size(); ++i) {
            int len = 0;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    len = max(len, dp[j]);
                }
            }
            dp[i] = len+1;
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }
};