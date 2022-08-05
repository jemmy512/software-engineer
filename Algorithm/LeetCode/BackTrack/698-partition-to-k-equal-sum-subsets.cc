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
The frequency of each element is in the range [1, 4].

Relatives:
416. Partition Equal Subset Sum
698. Partition to K Equal Sum Subsets
1981. Minimize the Difference Between Target and Chosen Elements
2025. Maximum Number of Ways to Partition an Array
2035. Partition Array Into Two Arrays to Minimize Sum Difference */

#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>

using namespace std;

/* from the perspective of bucket
 * O(k*2^n) */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (k > nums.size())
            return false;

        const auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % k != 0)
            return false;

        int used = 0;

        return backtrack(k, 0, nums, 0, sum / k, used);
    }

private:
    bool backtrack(const int bktI, const int bktISum, const vector<int>& nums, int pos, const int target, int used) {
        if (bktI == 0)
            return true;

        if (bktISum == target) {
            return Memo[used] = backtrack(bktI - 1, 0, nums, 0, target, used);
        }

        if (Memo.count(used)) {
            return Memo[used];
        }

        for (; pos < nums.size(); ++pos) {
            if ((used >> pos) & 1 == 1)
                continue;

            if (nums[pos] + bktISum > target)
                continue;

            used |= 1 << pos;
            if (backtrack(bktI, bktISum + nums[pos], nums, pos + 1, target, used)) {
                return true;
            }
            used ^= 1 << pos;
        }

        return false;
    }

private:
    unordered_map<int, int> Memo;
};

/* from the perspective of digit
 * O(k^n) */
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