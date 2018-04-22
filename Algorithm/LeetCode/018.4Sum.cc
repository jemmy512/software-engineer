/*
Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

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

Idea:
    1. Sort the vector
    2. Traverse the array and solve the problem by using '3Sum' solution

*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 282 test cases, 15ms, beat 98.09%
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
                        result.push_back(vector<int>{nums[i], nums[j], nums[low], nums[high]});
                        while (low < high && nums[low] == nums[low + 1])
                            ++low;
                        ++low;
                        while (low < high && nums[high - 1] == nums[high])
                            --high;
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

// 282 test cases, 60ms, beat 15.79%
class Solution_ {
public:
    static vector<vector<int>> threeSum(vector<int> &nums, int target) {
        int len = nums.size();
        vector<vector<int>> vec;
        int sum, low, high;
        for (int i = 0; i < len - 2; ++i) {
            low = i + 1;
            high = len - 1;
            while (low < high) {
                sum = nums[i] + nums[low] + nums[high];
                if (sum == target) {
                    vector<int> v = {nums[i], nums[low], nums[high]};
                    vec.push_back(v);
                    while (low < len - 1 && nums[low] == nums[low + 1])
                        ++low;
                    ++low;
                    while (high > 0 && nums[high - 1] == nums[high])
                        --high;
                    --high;
                } else if (sum > target) {
                    --high;
                } else {
                    ++low;
                }
            }
            while (nums[i] == nums[i + 1])
                ++i;
        }
        return vec;
    }
    
    static vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> vec;
        if (nums.size() < 4) 
            return vec;
        int len = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 0; i < len - 3; ++i) {
            vector<int> tmp(nums.begin() + i + 1, nums.end());
            vector<vector<int>> v = threeSum(tmp, target - nums[i]);
            for (int j = 0; j < v.size(); ++j) {
                v[j].insert(v[j].begin(), nums[i]);
                vec.push_back(v[j]);                
            }
            while (nums[i] == nums[i + 1])
                ++i;
        }
        
        return vec;
    }
};

int main() {
    vector<int> vec = {1,0,-1,0,-2,2};
    vector<vector<int>> ret = Solution::fourSum(vec, 0);
    for (auto vec : ret) {
        for (auto i : vec) {
            cout << i << ", ";
        }
        cout << endl;
    }
}