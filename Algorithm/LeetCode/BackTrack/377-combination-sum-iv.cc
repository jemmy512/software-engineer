/* Medium
Given an array of distinct integers nums and a target integer target,
return the number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.

Example 1:
Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.

Example 2:
Input: nums = [9], target = 3
Output: 0

Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 1000
All the elements of nums are unique.
1 <= target <= 1000

Follow up: What if negative numbers are allowed in the given array?
How does it change the problem? What limitation we need to add to the question
to allow negative numbers?

Relatives:
017. Letter Combinations of a Phone Number

078. Subsets
090. Subsets II

046. Permutations
047. Permutations II

077. Combinations
039. Combination Sum
040. Combination Sum II
216. Combination Sum III
377. Combination Sum IV */

#include <vector>
using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1; // Base case: one way to make sum 0 (empty combination)

        for (int i = 1; i <= target; ++i) {
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }

        return dp[target];
    }
};

// timeout
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        backtrack(nums, 0, target);

        return Result;
    }

private:
    void backtrack(const vector<int>& nums, int j, int remain) {
        if (remain < 0 || j == nums.size()) {
            return;
        }

        if (remain == 0) {
            ++Result;
            return;
        }

        for (auto i = 0; i < nums.size(); ++i) {
            remain -= nums[i];

            backtrack(nums, i, remain);

            remain += nums[i];
        }
    }

private:
    int Result = 0;
};