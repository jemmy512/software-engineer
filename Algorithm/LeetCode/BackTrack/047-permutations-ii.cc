/* Medium
Given a collection of numbers, nums, that might contain duplicates,
return all possible unique permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]

Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Constraints:
1 <= nums.length <= 8
-10 <= nums[i] <= 10 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        permute(nums, 0);

        return Result;
    }

private:
    void permute(vector<int>& nums, int pos) {
        if (pos == nums.size()) {
            Result.emplace_back(nums);
        } else {
            for (int i = pos; i < nums.size(); ++i) {
                if (canSwap(nums, pos, i)) {
                    swap(nums[pos], nums[i]);
                    permute(nums, pos + 1);
                    swap(nums[pos], nums[i]);
                }
            }
        }
    }

    bool canSwap(vector<int>& vec, int beg, int end) {
        while (beg < end && vec[beg] != vec[end]) {
            ++beg;
        }

        return beg == end;
    }

private:
    vector<vector<int>> Result;
};