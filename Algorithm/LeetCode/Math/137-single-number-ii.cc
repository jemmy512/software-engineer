/* Medium
Given an integer array nums where every element appears three times except for one,
which appears exactly once.
Find the single element and return it.

Example 1:
Input: nums = [2,2,3,2]
Output: 3
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99

Constraints:
1 <= nums.length <= 3 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
Each element in nums appears exactly three times except for one element which appears once.

Relatives:
136. Single Number
137. Single Number II
260. Single Number III
268. Missing Number
287. Find the Duplicate Number
389. Find the Difference
645. Set Mismatch */

#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

/* Solution: Bitwise Operators : NOT, AND and XOR */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int seenOnce = 0, seenTwice = 0;

        for (int num : nums) {
            // first appearence:
            // add num to seen_once
            // don't add to seen_twice because of presence in seen_once

            // second appearance:
            // remove num from seen_once
            // add num to seen_twice

            // third appearance:
            // don't add to seen_once because of presence in seen_twice
            // remove num from seen_twice
            seenOnce = ~seenTwice & (seenOnce ^ num);
            seenTwice = ~seenOnce & (seenTwice ^ num);
        }

        return seenOnce;
    }
};

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        long long sumAll = 0;
        long long sum = 0;
        unordered_set<int> hashSet;

        for (const auto& num : nums) {
            sumAll += num;
            hashSet.emplace(num);
        }

        sum = std::accumulate(hashSet.cbegin(), hashSet.cend(), (long long)0);

        return ((3*sum) - sumAll) / 2;
    }
};