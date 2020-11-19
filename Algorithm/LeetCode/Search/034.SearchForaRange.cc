/**
Difficulty: Medium

Given an array of integers nums sorted in ascending order, find the starting
 and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Solution:   Binary Search

*/

class Solution {
private:
    int extremeIndex(vector<int> &nums, int target, bool left) {
        int low = 0;
        int high = nums.size();
        while (low < high) {
            int pivot = low + (high-low)/2 ;
            if (nums[pivot] > target || (left && nums[pivot] == target)) {
                high = pivot;
            } else {
                low = pivot + 1;
            }
        }

        return low;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = extremeIndex(nums, target, true);
        if (low == nums.size() || nums[low] != target)
            return {-1, -1};

        int high = extremeIndex(nums, target, false) - 1;

        return {low, high};
    }
};

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {searchExtremePosition(nums, target, true), searchExtremePosition(nums, target, false)};
    }

private:
    int searchExtremePosition(const vector<int>& nums, int target, bool isFirst) {
        int low = 0;
        int high = nums.size();

        while (low < high) {
            int pivot = low + (high-low)/2;
            if (nums[pivot] > target) {
                high = pivot;
            } else if (nums[pivot] < target) {
                low = pivot + 1;
            } else {
                if (isFirst) {
                   if (pivot == 0 || nums[pivot-1] < nums[pivot]) {
                        return pivot;
                    } else {
                        high = pivot;
                    }
                } else {
                    if (pivot+1 == high || nums[pivot] < nums[pivot+1]) {
                        return pivot;
                    } else {
                        low = pivot + 1;
                    }
                }

            }
        }

        return low < nums.size() && nums[low] == target ? low : -1;
    }
};

class Solution_ {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> vec = {-1, -1};
        if (nums.empty()) return vec;

        int len = nums.size();
        int beg = 0, end = len - 1, pivot;
        while (beg <= end) {
            pivot = (beg + end) >> 1;
            if (nums[pivot] < target)
                beg = pivot + 1;
            else if (nums[pivot] > target)
                end = pivot - 1;
            else {
                beg = pivot - 1;
                while (beg > -1 && nums[beg] == target) --beg;
                end = pivot + 1;
                while (end < len && nums[end] == target) ++end;
                vec[0] = beg + 1;
                vec[1] = end - 1;
                break;
            }
        }

        return vec;
    }
};