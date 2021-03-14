/* Easy
 *
 * Given an array of integers, return indices of the two numbers such that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,return [0, 1].
 *
 * Constraints:
 * 2 <= nums.length <= 10^3
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 * Only one valid answer exists.
 *
 * Relatives:
 * 1. Two Sum
 * 167. Two Sum II - Input array is sorted
 * 170. Two Sum III - Data structure design
 * 653. Two Sum IV - Input is a BST
 * 1214. Two Sum BSTs */

#include <unordered_map>
#include <vector>

using std::vector;
using std::unordered_map;

class Solution {
public:
    /* One-pass Hash Table
     * Time Complexity: O(1),
     * Space complexity: O(1) */
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            if (map.find(target-nums[i]) != map.end())
               return {map[target-nums[i]], i};
            else
                map[nums[i]] = i;
        }

        return nums;
    }

    /* Brute Force
     * Time complexity : O(n^2)
     * pace complexity : O(1) */
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size()-1; ++i) {
            for (int j = i+1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }

        return nums;
    }
};
