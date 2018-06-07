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
        int lo = 0, mid;
        int hi = nums.size();
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            if (nums[mid] > target || (left && nums[mid] == target)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }   
    
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> vec = {-1, -1};
        int lo = extremeIndex(nums, target, true);
        if (lo == nums.size() || nums[lo] != target) return vec;
        
        vec[0] = lo;
        vec[1] = extremeIndex(nums, target, false) - 1;
        
        return vec;
    }
};

class Solution_ {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> vec = {-1, -1};
        if (nums.empty()) return vec;
        
        int len = nums.size();
        int beg = 0, end = len - 1, mid;
        while (beg <= end) {
            mid = (beg + end) >> 1;
            if (nums[mid] < target) 
                beg = mid + 1;
            else if (nums[mid] > target)
                end = mid - 1;
            else {
                beg = mid - 1;
                while (beg > -1 && nums[beg] == target) --beg;
                end = mid + 1;
                while (end < len && nums[end] == target) ++end;
                vec[0] = beg + 1;
                vec[1] = end - 1;
                break;
            }
        }
        
        return vec;
    }
};