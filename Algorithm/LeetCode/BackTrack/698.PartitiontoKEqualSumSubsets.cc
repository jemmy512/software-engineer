/* Medium
Given an integer array nums and an integer k,
return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.

Example 1:
Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

Example 2:
Input: nums = [1,2,3,4], k = 3
Output: false

Constraints:
1 <= k <= nums.length <= 16
1 <= nums[i] <= 10^4
The frequency of each element is in the range [1, 4]. */

#include <list>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/* from the perspective of bucket
 * O(k^n) */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (k > nums.size())
            return false;

        const auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % k != 0)
            return false;

        Used.resize(nums.size(), 0);

        return backtrack(k, 0, nums, 0, sum / k);
    }

private:
    bool backtrack(const int bktI, const int bktISum, const vector<int>& nums, int pos, const int target) {
        if (bktI == 0)
            return true;
        if (bktISum == target)
            return backtrack(bktI - 1, 0, nums, 0, target);

        for (; pos < nums.size(); ++pos) {
            if (Used[pos])
                continue;

            if (nums[pos] + bktISum > target)
                continue;

            Used[pos] = true;
            if (backtrack(bktI, bktISum + nums[pos], nums, pos + 1, target)) {
                return true;
            }
            Used[pos] = false;
        }

        return false;
    }

private:
    vector<int> Used;
};

/* from the perspective of digit
 * O(k*2^n) */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (k > nums.size())
            return false;

        const auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % k != 0)
            return false;

        Bucket.resize(k, 0);
        std::sort(nums.begin(), nums.end(), std::greater());

        return backtrack(nums, 0, sum / k);
    }

private:
    bool backtrack(const vector<int>& nums, int pos, int target) {
        if (pos == nums.size()) {
            for (const auto& sum : Bucket) {
                if (sum != target) {
                    return false;
                }
            }

            return true;
        }

        for (auto& sum : Bucket) {
            if (nums[pos] + sum <= target) {
                sum += nums[pos];
                if (backtrack(nums, pos + 1, target)) {
                    return true;
                }
                sum -= nums[pos];
            }
        }

        return false;
    }

private:
    vector<int> Bucket;
};