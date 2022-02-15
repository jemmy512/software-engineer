/* Easy
You have a set of integers s, which originally contains all the numbers from 1 to n.
Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set,
which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]

Example 2:
Input: nums = [1,1]
Output: [1,2]

Constraints:
2 <= nums.length <= 10^4
1 <= nums[i] <= 10^4

Relatives:
136. Single Number
137. Single Number II
260. Single Number III
268. Missing Number
287. Find the Duplicate Number
389. Find the Difference
645. Set Mismatch */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        auto missing = nums.size();
        for (auto i = 1; i <= nums.size(); ++i) {
            missing ^= i ^ nums[i-1];
        }
    }
};