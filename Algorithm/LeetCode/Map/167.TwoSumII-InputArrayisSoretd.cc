/* Easy
Given an array of integers that is already sorted in ascending order,
find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target,
where index1 must be less than index2. Please note that your returned answers
(both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include<iostream>
#include<vector>
using namespace std;

/* Approaches:
 * 1. hash table
 * 2. two pointers */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int low = 0, high = numbers.size() - 1;

        while (low < high) {
            int sum = numbers[low] + numbers[high];
            if (sum == target)
                return {low + 1, high + 1};
            else if (sum < target)
                ++low;
            else
                --high;
        }

        return {-1, -1};
    }
};