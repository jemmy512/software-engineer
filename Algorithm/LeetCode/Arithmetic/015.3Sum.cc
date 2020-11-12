/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
#include<iostream>
#include<vector>
using namespace std;


// 313 test cases, 131 ms, beast 37.42% -> 56.15%
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> vec;
        int sum, low, high;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < len - 2; ++i) {
            // skip the duplication
            // if (i > 0 && nums[i - 1] == nums[i])
            //     continue;

            low = i + 1;
            high = len - 1;
            while (low < high) {
                sum = nums[i] + nums[low] + nums[high];
                if (sum == 0) {
                    vec.push_back({nums[i], nums[low], nums[high]});
                    while (low < len - 1 && nums[low] == nums[low + 1]) ++low;
                    while (high > low && nums[high -1] == nums[high]) -- high;
                    ++low;
                    --high;
                } else if (sum > 0) {
                    while (high > low && nums[high -1] == nums[high])
                        -- high;
                    --high;
                } else {
                    while (low < len - 1 && nums[low] == nums[low + 1])
                        ++low;
                    ++low;
                }
            }
            while (i + 1 < nums.size() && nums[i + 1] == nums[i])
                ++i;
        }
        return vec;
    }
};

int main() {

}