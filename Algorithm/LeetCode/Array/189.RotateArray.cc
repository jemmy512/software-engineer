/* Medium
Given an array, rotate the array to the right by k steps, where k is non-negative.

Follow up:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
Could you do it in-place with O(1) extra space?

Example 1:
Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:
Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:
1 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^5

Relatives:
061. Roate List By K
189. Rotate Array
725. Split Linked List in Parts */

#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

// 34 test case, 21ms, beat 85.77%
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        int newK = len - k % len;
        int lenTail = len - newK;
        nums.insert(nums.begin(), nums.begin() + newK, nums.end());
        nums.erase(nums.end() - lenTail, nums.end());
    }

    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        int cnt = len - k % len;

        while (cnt--) {
            auto beg = nums.begin() + cnt - 1;
            while (beg != nums.end()-1) {
                std::swap(*beg, *(beg+1));
                ++beg;
            }
        }
    }

};

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        int newK = k % len;
        int cnt = len - newK;

        while (cnt--) {
            auto beg = nums.begin() + cnt;
            auto end = beg + newK;
            while (beg != end && end < nums.end()) {
                std::swap(*beg, *(beg+1));
                ++beg;
            }
        }
    }
};
/*
Edge case:
[1] 1
[1, 2] 3
*/