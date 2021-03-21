/* Easy
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
find the one that is missing from the array.

Example 1:
Input: [3,0,1]
Output: 2

Example 2:
Input: [9,6,4,2,3,5,7,0,1]
Output: 8

Note:
Your algorithm should run in linear runtime complexity.
Could you implement it using only constant extra space complexity?

Relatives:
136. Single Number
137. Single Number II
260. Single Number III
268. Missing Number
287. Find the Duplicate Number
389. Find the Difference
645. Set Mismatch */


#include<iostream>
#include<vector>

using namespace std;

/* Solutions:
 * 1. sorting
 * 2. hash set
 * 3. bit maniupulation
 * 4. Gauss' Formula */

class Solution {
public:
    // This problem can be converted to the classic problem --
    // `There is an array, all of numbers except one appears twice, and that one only appears once`
    // It means, we can combin two arrays together, one is [1..n], another one is `nums`.
    // Then, you know, we can use the XOR solve this problem.

    int missingNumber(vector<int>& nums) {
        int len = nums.size();
        int missing = len;

        for (int i = 0; i < len; ++i)
            missing ^= i ^ nums[i];

        return missing;
    }
};