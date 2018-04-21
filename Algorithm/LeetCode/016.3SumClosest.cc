/*
Given an array nums of n integers and an integer target, find three integers 
    in nums such that the sum is closest to target. Return the sum of the three
    integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
#include<iostream>
#include<climits>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;

class Solution {
public:
    static int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int sum, tmp;
        int distance = INT_MAX;
        int i = 0;
        int j;
        int k = nums.size() - 1;
        while (i + 2 < k) {
            if (distance == 0)
                return sum;
            j = i + 1;
            tmp = nums[i] + nums[j] + nums[k];
            if (tmp == target) {
                return tmp;
            } else if (tmp > target) {
                while (nums[k - 1] == nums[k]) 
                    --k;
                --k;
                tmp = nums[i] + nums[j] + nums[k];
                if (abs(tmp -target) < distance) {
                    sum = tmp;
                    distance = abs(tmp - target);
                }
            } else {
                while (nums[j - 1] == nums[j]) ++j;
                while (j < k) {
                    tmp = nums[i] + nums[j] + nums[k];
                    if (abs(tmp - target) < distance) {
                        sum = tmp;
                        distance = abs(tmp - target);
                    } else 
                        break;
                    ++j;
                }
                ++i;
                while (nums[i - 1] == nums[i]) ++i;
            }
        }
        return sum;
    }
};

int main() {
    vector<int> vec = {1,2,4,8,16,32,64,128};
    cout << Solution::threeSumClosest(vec, 82) << endl;
}