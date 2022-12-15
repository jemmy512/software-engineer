/* [442] Find All Duplicates in an Array
 *
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/description/
 *
 * algorithms
 * Medium (73.39%)
 * Likes:    7751
 * Dislikes: 296
 * Total Accepted:    477.5K
 * Total Submissions: 650.3K
 * Testcase Example:  '[4,3,2,7,8,2,3,1]'
 *
 * Given an integer array nums of length n where all the integers of nums are
 * in the range [1, n] and each integer appears once or twice, return an array
 * of all the integers that appears twice.
 *
 * You must write an algorithm that runs in O(n) time and uses only constant
 * extra space.
 *
 * Example 1:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [2,3]
 *
 * Example 2:
 * Input: nums = [1,1,2]
 * Output: [1]
 *
 * Example 3:
 * Input: nums = [1]
 * Output: []
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 10^5
 * 1 <= nums[i] <= n
 * Each element in nums appears once or twice. */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        const auto size = nums.size();

        for (auto i = 0; i < nums.size(); ++i) {
            while (nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (auto i = 0; i < size; ++i) {
            if (nums[i] - 1 != i) {
                result.push_back(nums[i]);
            }
        }

        return result;
    }
};