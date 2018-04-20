/*
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/
#include<iostream>
#include<vector>
using namespace std;

// 17/17 test cases, 6ms, beat 99.69%
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ret;
        int i = 0;
        int j  = numbers.size() - 1;
        while (i < j) {
            if (numbers[i] + numbers[j] < target) {
                ++i;
            } else if (numbers[i] + numbers[j] > target) {
                --j;
            } else {
                ret.push_back(i + 1);
                ret.push_back(j + 1);
                return ret;
            }
        }
        
        return ret;
    }
};