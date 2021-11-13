/* Medium
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-'
before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1
and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the rest of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:
Input: nums = [1], target = 1
Output: 1

Constraints:
1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= rest(nums[i]) <= 1000
-1000 <= target <= 1000

Relatives:
494. Target Sum
282. Expression Add Operators */

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

/* knapsack
sum(A) - sum(B) = target
sum(A) = target + sum(B)
sum(A) + sum(A) = target + sum(B) + sum(A)
2 * sum(A) = target + sum(nums) */

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);

        if (sum < target || (sum + target) % 2 == 1) {
            return 0;
        }

        return subsets(nums, (sum + target) / 2);
    }

private:
    int subsets(const vector<int>& nums, int sum) {
        if (sum < 0)
            return 0;

        const auto len = nums.size();
        vector<vector<int>> dp = vector(len + 1, vector(sum + 1, 0));

        for (int i = 0; i <= len; i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= len; i++) {
            for (int j = 0; j <= sum; j++) {
                if (j >= nums[i-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[len][sum];
    }
};

// dp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        if (nums.size() == 0)
            return 0;

        return dp(nums, 0, target);
    }

private:
    int dp(const vector<int>& nums, int i, int rest) {
        if (i == nums.size()) {
            return (rest == 0) ? 1 : 0;
        }

        const auto key = to_string(i) + "," + to_string(rest);
        if (Memo.find(key) != Memo.end()) {
            return Memo[key];
        }

        auto value = dp(nums, i+1, rest - nums[i]) + dp(nums, i+1, rest + nums[i]);
        Memo.emplace(key, value);

        return value;
    }

private:
    unordered_map<string, int> Memo;
    /* 'unordered_map<
            std::pair<int, int>,
            int,
            std::hash<std::pair<int, int>>,
            std::equal_to<std::pair<int, int>>,
            std::allocator<std::pair<const std::pair<int, int>, int>>>'
        is implicitly deleted because field '_M_h' has a deleted default constructor _Hashtable _M_h
    * unordered_map<pair<int, int>, int> Memo; */
};

// backtrack
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        backtrack(nums, 0, target);

        return Count;
    }

private:
    void backtrack(const vector<int>& nums, int idx, int rest) {
        if (idx >= nums.size()) {
            if (rest == 0)
                ++Count;
        } else {
            backtrack(nums, idx+1, rest - nums[idx]); // add '+'
            backtrack(nums, idx+1, rest + nums[idx]); // add '-'
        }
    }

private:
    int Count{0};
};