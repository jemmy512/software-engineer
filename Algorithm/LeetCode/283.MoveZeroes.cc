/*
Difficulty: Easy

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

*/

// 21 test cases, 16ms, beat 99.04%
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        size_t free = -1;
        for (size_t i = 0; i < len; ++i) {
            if (nums[i] == 0) {
                if (free == -1)
                    free = i;
                continue;
            } else {
                if (free != -1)
                    swap(nums[free++], nums[i]);
            }
        }
    }
};

// 21 test cases, 17ms, beat 80.04%
class Solution_ {
public:
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        int j = 0;
        for (; j < len && nums[j]; ++j);
        for (int i = 0; i < len; ++i) {
            if (nums[i] != 0 && i > j) {
                swap(nums[i], nums[j++]);
                for (; j < len && nums[j]; ++j);
            } 
        }
    }
};