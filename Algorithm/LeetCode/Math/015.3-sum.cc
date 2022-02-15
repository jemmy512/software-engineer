/* Medium
Given an integer array nums, return all the triplets
[nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k,
and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Example 2:
Input: nums = []
Output: []

Example 3:
Input: nums = [0]
Output: []

Constraints:
0 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() && nums[i] <= 0; ++i) {
            if (i == 0 || nums[i-1] != nums[i]) {
                twoSum(nums, i);
            }
        }

        return result;
    }

private:
    void twoSum(const vector<int>& nums, int i) {
        int low = i + 1;
        int high = nums.size() - 1;

        while (low < high) {
            int sum = nums[i] + nums[low] + nums[high];
            if (sum == 0) {
                result.push_back({nums[i], nums[low++], nums[high--]});
            } else if (sum < 0) {
                ++low;
            } else {
                --high;
            }

            while (low < high && low > i+1 && nums[low-1] == nums[low])
                ++low;
            while (low < high && high < nums.size()-1 && nums[high] == nums[high+1])
                --high;
        }
    }

private:
    vector<vector<int>> result;
};