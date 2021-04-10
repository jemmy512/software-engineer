/* Medium
Given an array nums of n integers and an integer target,
are there elements a, b, c, and d in nums such that a + b + c + d = target?
Find all unique quadruplets in the array which gives the sum of target.

Note:
The solution set must not contain duplicate quadruplets.

Example:
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

Constraints:
1 <= nums.length <= 200
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9

Idea:
    1. Sort the vector
    2. Traverse the array and solve the problem by using '3Sum' solution

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 0, 4);
    }

    vector<vector<int>> kSum(vector<int>& nums, int target, int beg, int k) {
        vector<vector<int>> result;

        if (beg == nums.size() || nums[beg] * k > target || target > nums.back() * k)
            return result;
        if (k == 2)
            return twoSum(nums, target, beg);

        for (int i = beg; i < nums.size(); ++i) {
            if (i == beg || nums[i - 1] != nums[i]) {
                for (auto &set : kSum(nums, target - nums[i], i + 1, k - 1)) {
                    result.push_back({nums[i]});
                    result.back().insert(result.back().end(), set.begin(), set.end());
                }
            }
        }

        return result;
    }

    vector<vector<int>> twoSum(vector<int>& nums, int target, int beg) {
        vector<vector<int>> result;
        int lo = beg, hi = nums.size() - 1;

        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            if (sum == target) {
                result.push_back({nums[lo++], nums[hi--]});
            } else if (sum < target) {
                ++lo;
            } else {
                --hi;
            }

            while (lo < hi && lo > beg && nums[lo-1] == nums[lo])
                ++lo;
            while (lo < hi && hi < nums.size()-1 && nums[hi] == nums[hi+1])
                --hi;
        }

        return result;
    }
};

class Solution {
public:
    static vector<vector<int>> fourSum(vector<int> &nums, int target) {
       vector<vector<int>> result;
        int len = nums.size();
        if (len < 4)
            return result;

        int sum, low, high;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < len - 3; ++i) {
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break;
            if (nums[i] + nums[len - 1] + nums[len - 2] + nums[len - 3] < target)
                continue;

            for (int j = i + 1; j < len - 2; ++j) {
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
                    break;
                if (nums[i] + nums[j] + nums[len - 1] + nums[len - 2] < target)
                    continue;

                low = j + 1;
                high = len - 1;
                while (low < high) {
                    sum = nums[i] + nums[j] + nums[low] + nums[high];
                    if (sum == target) {
                        result.push_back({nums[i], nums[j], nums[low++], nums[high--]});
                        while (low < high && nums[low-1] == nums[low])
                            ++low;
                        while (low < high && nums[high] == nums[high+1])
                            --high;
                    } else if (sum > target) {
                        --high;
                    } else {
                        ++low;
                    }
                }
                while (j < len - 2 && nums[j] == nums[j + 1])
                    ++j;
            }
            while (i < len - 3 && nums[i] == nums[i + 1])
                ++i;
        }

        return result;
    }
};
